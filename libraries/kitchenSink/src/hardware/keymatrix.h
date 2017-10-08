#ifndef INCLUDED_KEYMATRIX_H
#define INCLUDED_KEYMATRIX_H

#include "hardware/keymask.h"

#include <array>
#include <cstddef>
#include <cstdint>

class EntropyPool;

class KeyMatrix
{
public:
    static void setup();
    
public:
    KeyMatrix(const int      addr,
              const uint16_t rowMask,
              const uint16_t colMask,
              EntropyPool&   entropyPool);

public:
    void scan();

private:
    void init();
    
private:
    const int      mAddr;
    const uint16_t mRowMask;
    const uint16_t mColMask;

    EntropyPool& mEntropyPool;
    uint8_t      mCounter;
    
public:
    KeyMask state;
    
private:
    KeyMatrix(const KeyMatrix&) = delete;
    KeyMatrix& operator=(const KeyMatrix&) = delete;
};



#endif









