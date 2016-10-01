#include "keymatrix.h"

#include <Wire.h>

void KeyMatrix::init()
{
    Wire.begin();
    Wire.setClock(1000000);
}

KeyMatrix::KeyMatrix(int addr, uint16_t rowMask, uint16_t colMask)
    : mAddr(addr)
    , mRowMask(rowMask)
    , mColMask(colMask)
    , mState()
    , mDelta() 
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

bool KeyMatrix::scan()
{
    bool hasDelta(false);
    
    std::size_t index(0);
    int rowMask(mRowMask);

    uint8_t maskData[2];

    while (rowMask && (index < mState.size()))
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

        Mask::Row row((~Wire.read()) & 0xff);

        Wire.beginTransmission(mAddr);
        Wire.write(0x13);
        Wire.endTransmission();
        Wire.requestFrom(mAddr, 1);
        
        row |= (((~Wire.read()) & 0xff) << 8);
        row &= mColMask;
        
        mDelta[index] = mState[index];
        mDelta[index] ^= row;
        mState[index] = row;
        
        hasDelta |= !mDelta[index].empty();
        
        rowMask &= ~rowBit;
        ++index;
    }

    return hasDelta;
}
