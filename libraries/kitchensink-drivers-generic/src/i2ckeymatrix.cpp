#include "i2ckeymatrix.h"

#include "mcp23017.h"
#include "crypto/entropypool.h"

#include <Wire.h>

void I2CKeyMatrix::setup()
{
    Wire.begin();
    Wire.setClock(1000000L);
}

I2CKeyMatrix::I2CKeyMatrix(uint8_t      addr,
                           uint16_t     rowMask,
                           uint16_t     colMask,
                           EntropyPool& entropyPool)
    : mAddr(addr)
    , mRowMask(rowMask)
    , mColMask(colMask)
    , mEntropyPool(entropyPool)
    , mCounter(0)
{
    init();
}

void I2CKeyMatrix::init()
{
    Wire.beginTransmission(mAddr);
    Wire.write(MCP23017::IODIRA);
    Wire.write(mColMask & 0xff);
    Wire.endTransmission();

    Wire.beginTransmission(mAddr);
    Wire.write(MCP23017::IODIRB);
    Wire.write((mColMask >> 8) & 0xff);
    Wire.endTransmission();

    Wire.beginTransmission(mAddr);
    Wire.write(MCP23017::GPPUA);
    Wire.write(mColMask & 0xff);
    Wire.endTransmission();
    
    Wire.beginTransmission(mAddr);
    Wire.write(MCP23017::GPPUB);
    Wire.write((mColMask >> 8) & 0xff);
    Wire.endTransmission();
}

uint16_t I2CKeyMatrix::scan(uint16_t& rowMask)
{
    uint16_t rowBit(rowMask & -rowMask);
    uint8_t maskData[2];
        
    if (rowBit & 0xff)
    {
        maskData[0] = MCP23017::GPIOA;
        maskData[1] = ~(rowBit & 0xff);
    }
    else
    {
        maskData[0] = MCP23017::GPIOB;
        maskData[1] = ~((rowBit >> 8) & 0xff);
    }

    Wire.beginTransmission(mAddr);
    Wire.write(maskData, 2);
    Wire.endTransmission();

    Wire.beginTransmission(mAddr);
    Wire.write(MCP23017::GPIOA);
    Wire.endTransmission();
    Wire.requestFrom(mAddr, (uint8_t)1);

    uint16_t row((~Wire.read()) & 0xff);

    Wire.beginTransmission(mAddr);
    Wire.write(MCP23017::GPIOB);
    Wire.endTransmission();
    Wire.requestFrom(mAddr, (uint8_t)1);
        
    row |= (((~Wire.read()) & 0xff) << 8);
    row &= mColMask;

    rowMask &= ~rowBit;

    return row;
}
