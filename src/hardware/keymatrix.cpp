#include "keymatrix.h"

#include "hardware/entropypool.h"

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

        // Row changes (ie physical key presses or releases) write the value of
        // the entropy pool counter into the entropy pool.
        //
        // Given that the matrix should scan at approximately 500hz with a row
        // count of usually 5, this makes the value of the counter completely
        // unpredictable - it will be derived from both the row location of the
        // key and the time of the event at a granularity of approximately 2
        // milliseconds.
        //
        // This will also write any key bounces, seeing as we haven't gone
        // through the debounce filter yet.
        
        if (row != state[index])
        {
            mEntropyPool.insert(mCounter);
            state[index] = row;
        }
        
        // Counter is incremented for every row scan to incorporate the row
        // location of the key into the entropy pool.
        //
        // We wrap the value using a prime number rather than allowing it to
        // overflow so that a row count divisible by 256 (ie usually 4 or 8)
        // cannot be exploited to derive the row number of the key from the
        // entropy pool by examining the lower bits of the counter values.
        //
        // It also makes it more difficult for an attacker to advantage of the
        // higher bits being derived from the time of the event at a higher
        // granularity.
        //
        // These cases are quite unlikely to be exploitable in any meaningful
        // way, but it's good practice to make things as difficult as possible
        // for any potential attacks that we haven't thought of.
        //
        // This will of course cost us a little bit of entropy (0 - 250 entering
        // the pool rather than 0 - 255), but we're going to normalise the
        // random output by using a hash function on a range of input larger
        // than the resulting hash value.
        
        mCounter = (mCounter + 1) % 251;

        // Move to the next bit in the row mask and increment.
        rowMask &= ~rowBit;
        ++index;
    }
}
