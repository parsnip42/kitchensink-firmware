#include "hardware/i2ckeymatrix.h"

#include "hardware/mcp23017.h"
#include "crypto/entropypool.h"

#include <Wire.h>

void I2CKeyMatrix::setup()
{
    Wire.begin();
    Wire.setClock(1000000L);
}

I2CKeyMatrix::I2CKeyMatrix(const int      addr,
                           const uint16_t rowMask,
                           const uint16_t colMask,
                           EntropyPool&   entropyPool)
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

const KeyMask& I2CKeyMatrix::scan()
{
    std::size_t index(0);
    int rowMask(mRowMask);

    uint8_t maskData[2];

    while (rowMask && (index < KeyMask::kRows))
    {
        uint16_t rowBit(rowMask & -rowMask);
        
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
        Wire.requestFrom(mAddr, 1);

        KeyMask::Row row((~Wire.read()) & 0xff);

        Wire.beginTransmission(mAddr);
        Wire.write(MCP23017::GPIOB);
        Wire.endTransmission();
        Wire.requestFrom(mAddr, 1);
        
        row |= (((~Wire.read()) & 0xff) << 8);
        row &= mColMask;

        // Row changes (ie physical key presses or releases) write a value
        // derived from the matrix scan counter and the row of the key into the
        // entropy pool. We *could* incorporate the column too, but unless
        // absolutely necessary it's probably best to ensure that this thing
        // doesn't in any conceivable way turn itself into a key logger.
        //
        // The counter is an unsigned octet which is incremented every full
        // scan, so will range from 0 - 255 as it wraps at approximately every
        // 0.5s. The final value to be inserted into the entropy pool is the
        // counter value + row index.
        //
        // This will also write any key bounces, seeing as we haven't gone
        // through the debounce filter yet.
        
        if (row != mState[index])
        {
            mEntropyPool.insert(mCounter + index);
            mState[index] = row;
        }

        // Move to the next bit in the row mask and increment.
        rowMask &= ~rowBit;
        ++index;
    }

    ++mCounter;

    return mState;
}
