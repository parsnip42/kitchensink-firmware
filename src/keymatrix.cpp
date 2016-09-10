#include "keymatrix.h"

#include "Wire.h"

KeyMatrix::KeyMatrix(int addr, uint16_t rowMask, uint16_t colMask)
    : mAddr(addr)
    , mRowMask(rowMask)
    , mColMask(colMask)
    , mState()
    , mDelta() 
{
    init();
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
    
    while (rowMask && (index < mState.size()))
    {
        uint16_t rowBit(rowMask & -rowMask);

        if (rowBit & 0xff)
        {    
            Wire.beginTransmission(mAddr);
            Wire.write(0x12);
            Wire.write(~(rowBit & 0xff));
            Wire.endTransmission();
        }
        
        if ((rowBit >> 8) & 0xff)
        {    
            Wire.beginTransmission(mAddr);
            Wire.write(0x13);
            Wire.write(~((rowBit >> 8) & 0xff));
            Wire.endTransmission();
        }

        Mask::Row row;
        
        Wire.beginTransmission(mAddr);
        Wire.write(0x12);
        Wire.endTransmission();
        Wire.requestFrom(mAddr, 1);
        row.data() = ((~Wire.read()) & 0xff);

        Wire.beginTransmission(mAddr);
        Wire.write(0x13);
        Wire.endTransmission();
        Wire.requestFrom(mAddr, 1);
        row.data() |= (((~Wire.read()) & 0xff) << 8);
        row.data() &= mColMask;

        mDelta[index].data() = mState[index].data() ^ row.data();
        mState[index].data() = row.data();
        
        rowMask &= ~rowBit;
        ++index;
    }
}
