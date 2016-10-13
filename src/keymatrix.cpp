#include "keymatrix.h"

#include <Wire.h>

void KeyMatrix::init()
{
    Wire.begin();
    Wire.setClock(1000000);
}

KeyMatrix::KeyMatrix(const int      addr,
                     const uint16_t rowMask,
                     const uint16_t colMask)
    : mAddr(addr)
    , mRowMask(rowMask)
    , mColMask(colMask)
    , mState()
{
    config();
}

void KeyMatrix::config()
{
    Wire.beginTransmission(mAddr);
    Wire.write(0x00);
    Wire.write(mColMask & 0xff);
    Wire.endTransmission();

    Wire.beginTransmission(mAddr);
    Wire.write(0x01);
    Wire.write((mColMask >> 8) & 0xff);
    Wire.endTransmission();

    Wire.beginTransmission(mAddr);
    Wire.write(0xc);
    Wire.write(mColMask & 0xff);
    Wire.endTransmission();
    
    Wire.beginTransmission(mAddr);
    Wire.write(0xd);
    Wire.write((mColMask >> 8) & 0xff);
    Wire.endTransmission();
}

void KeyMatrix::scan()
{
    std::size_t index(0);
    int rowMask(mRowMask);

    uint16_t maskData;

    while (rowMask && (index < KeyMask::kRows))
    {
        uint16_t rowBit(rowMask & -rowMask);
        
        if (rowBit & 0xff)
        {
            maskData = (0x12 << 8) | ~(rowBit & 0xff);
        }
        else
        {
            maskData = (0x13 << 8) | ~((rowBit >> 8) & 0xff);
        }

        Wire.beginTransmission(mAddr);
        Wire.write(reinterpret_cast<uint8_t*>(&maskData), 2);
        Wire.endTransmission();

        Wire.beginTransmission(mAddr);
        Wire.write(0x12);
        Wire.endTransmission();
        Wire.requestFrom(mAddr, 1);

        auto& row(mState[index]);
        
        row = ((~Wire.read()) & 0xff);

        Wire.beginTransmission(mAddr);
        Wire.write(0x13);
        Wire.endTransmission();
        Wire.requestFrom(mAddr, 1);
        
        row |= (((~Wire.read()) & 0xff) << 8);
        row &= mColMask;
        
        rowMask &= ~rowBit;
        ++index;
    }
}
