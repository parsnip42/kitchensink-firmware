#ifndef INCLUDED_KEYMATRIX_H
#define INCLUDED_KEYMATRIX_H

#include "bitmask2d.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <functional>

class KeyMatrix
{
public:
    static const int kRows    = 5;
    static const int kColumns = 16;

    typedef Bitmask2d<kColumns, kRows> Mask;

public:
    KeyMatrix(int addr, uint16_t rowMask, uint16_t colMask);

public:
    void scan();

    const Mask::Row& operator[](std::size_t n) const;
    const Mask& state() const;
    const Mask& delta() const;
    
private:
    void init();
    
private:
    const int      mAddr;
    const uint16_t mRowMask;
    const uint16_t mColMask;

    Mask mState;
    Mask mDelta;
    
private:
    KeyMatrix(const KeyMatrix&) = delete;
    KeyMatrix& operator=(const KeyMatrix&) = delete;
};


inline
const KeyMatrix::Mask::Row& KeyMatrix::operator[](std::size_t n) const
{
    return mState[n];
}

inline
const KeyMatrix::Mask& KeyMatrix::state() const
{
    return mState;
}

inline
const KeyMatrix::Mask& KeyMatrix::delta() const
{
    return mDelta;
}

#endif
