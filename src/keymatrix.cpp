#include "keymatrix.h"

#include <Wire.h>

namespace
{
namespace Reg
{
constexpr uint8_t IODIRA = 0x00;
constexpr uint8_t IODIRB = 0x01;
constexpr uint8_t GPPUA  = 0x0c;
constexpr uint8_t GPPUB  = 0x0d;
constexpr uint8_t GPIOA  = 0x12;
constexpr uint8_t GPIOB  = 0x13;
}
}

void KeyMatrix::setup()
{
    Wire.begin();

    //Wire.setClock(100000L);
    //Wire.setClock(400000L);
    Wire.setClock(1000000L);
}

void KeyMatrix::init()
{
    Wire.beginTransmission(mAddr);
    Wire.write(Reg::IODIRA);
    Wire.write(mColMask & 0xff);
    Wire.endTransmission();

    Wire.beginTransmission(mAddr);
    Wire.write(Reg::IODIRB);
    Wire.write((mColMask >> 8) & 0xff);
    Wire.endTransmission();

    Wire.beginTransmission(mAddr);
    Wire.write(Reg::GPPUA);
    Wire.write(mColMask & 0xff);
    Wire.endTransmission();
    
    Wire.beginTransmission(mAddr);
    Wire.write(Reg::GPPUB);
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
            maskData[0] = Reg::GPIOA;
            maskData[1] = ~(rowBit & 0xff);
        }
        else
        {
            maskData[0] = Reg::GPIOB;
            maskData[1] = ~((rowBit >> 8) & 0xff);
        }

        Wire.beginTransmission(mAddr);
        Wire.write(maskData, 2);
        Wire.endTransmission();

        Wire.beginTransmission(mAddr);
        Wire.write(Reg::GPIOA);
        Wire.endTransmission();
        Wire.requestFrom(mAddr, 1);

        auto& row(mState[index]);
        
        row = ((~Wire.read()) & 0xff);

        Wire.beginTransmission(mAddr);
        Wire.write(Reg::GPIOB);
        Wire.endTransmission();
        Wire.requestFrom(mAddr, 1);
        
        row |= (((~Wire.read()) & 0xff) << 8);
        row &= mColMask;
        
        rowMask &= ~rowBit;
        ++index;
    }
}
