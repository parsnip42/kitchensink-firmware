#ifndef INCLUDED_KEYMATRIX_H
#define INCLUDED_KEYMATRIX_H

#include "bitmask2d.h"

#include <array>
#include <cstddef>
#include <cstdint>

class KeyMatrix
{
public:
    static const int kRows    = 5;
    static const int kColumns = 16;

    typedef Bitmask2d<kColumns, kRows> Mask;

public:
    static void init();
    
public:
    KeyMatrix(int addr, uint16_t rowMask, uint16_t colMask);

public:
    bool scan();
    
    const Mask& state() const;
    
private:
    void config();
    
private:
    const int      mAddr;
    const uint16_t mRowMask;
    const uint16_t mColMask;

    Mask mState;
    
private:
    KeyMatrix(const KeyMatrix&) = delete;
    KeyMatrix& operator=(const KeyMatrix&) = delete;
};


inline
const KeyMatrix::Mask& KeyMatrix::state() const
{
    return mState;
}

#endif
