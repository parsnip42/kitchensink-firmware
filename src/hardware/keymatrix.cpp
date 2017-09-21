#include "keymatrix.h"

#include "crypto/entropypool.h"

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

KeyMatrix::KeyMatrix(const int      addr,
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

        KeyMask::Row row((~Wire.read()) & 0xff);

        Wire.beginTransmission(mAddr);
        Wire.write(Reg::GPIOB);
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
        // counter bit rotated by the row index.
        //
        // This will also write any key bounces, seeing as we haven't gone
        // through the debounce filter yet.
        
        if (row != state[index])
        {
            auto rot(index & 7);
            mEntropyPool.insert((mCounter << rot) | (mCounter >> (8 - rot)));
            state[index] = row;
        }

        // Move to the next bit in the row mask and increment.
        rowMask &= ~rowBit;
        ++index;
    }

    ++mCounter;
}
