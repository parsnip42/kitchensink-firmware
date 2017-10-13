#ifndef INCLUDED_I2CKEYMATRIX_H
#define INCLUDED_I2CKEYMATRIX_H

#include "crypto/entropypool.h"
#include "types/bitmask2d.h"

#include <array>
#include <cstddef>
#include <cstdint>

class EntropyPool;

class I2CKeyMatrix
{
public:
    static void setup();
    
public:
    I2CKeyMatrix(const int      addr,
                 const uint16_t rowMask,
                 const uint16_t colMask,
                 EntropyPool&   entropyPool);

public:
    template <std::size_t Width, std::size_t Height>
    void scan(Bitmask2d<Width, Height>& keyMask);

private:
    void init();
    uint16_t scan(uint16_t& rowMask);
    
private:
    const int      mAddr;
    const uint16_t mRowMask;
    const uint16_t mColMask;

    EntropyPool& mEntropyPool;
    uint8_t      mCounter;
    
private:
    I2CKeyMatrix(const I2CKeyMatrix&) = delete;
    I2CKeyMatrix& operator=(const I2CKeyMatrix&) = delete;
};


template <std::size_t Width, std::size_t Height>
inline
void I2CKeyMatrix::scan(Bitmask2d<Width, Height>& keyMask)
{
    std::size_t index(0);
    uint16_t rowMask(mRowMask);

    while (index < Height && rowMask)
    {
        auto row(scan(rowMask));

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

        if (keyMask[index] != row)
        {
            mEntropyPool.insert(mCounter + index);
            keyMask[index] = row;
        }

        ++index;
    }

    ++mCounter;
}

#endif








