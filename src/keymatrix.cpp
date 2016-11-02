#include "keymatrix.h"

#include <Wire.h>

void KeyMatrix::setup()
{
    Wire.begin();
    Wire.setClock(1000000);
}

void KeyMatrix::init()
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

    uint8_t maskData[2];

    while (rowMask && (index < KeyMask::kRows))
    {
        uint16_t rowBit(rowMask & -rowMask);
        
        if (rowBit & 0xff)
        {
            maskData[0] = 0x12;
            maskData[1] = ~(rowBit & 0xff);
        }
        else
        {
            maskData[0] = 0x13;
            maskData[1] = ~((rowBit >> 8) & 0xff);
        }

        Wire.beginTransmission(mAddr);
        Wire.write(maskData, 2);
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
