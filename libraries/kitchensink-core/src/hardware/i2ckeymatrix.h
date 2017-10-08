#ifndef INCLUDED_I2CKEYMATRIX_H
#define INCLUDED_I2CKEYMATRIX_H

#include "hardware/keymask.h"

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
    const KeyMask& scan();

private:
    void init();
    
private:
    const int      mAddr;
    const uint16_t mRowMask;
    const uint16_t mColMask;

    EntropyPool& mEntropyPool;
    uint8_t      mCounter;
    KeyMask      mState;
    
private:
    I2CKeyMatrix(const I2CKeyMatrix&) = delete;
    I2CKeyMatrix& operator=(const I2CKeyMatrix&) = delete;
};

#endif








