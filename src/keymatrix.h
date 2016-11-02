#ifndef INCLUDED_KEYMATRIX_H
#define INCLUDED_KEYMATRIX_H

#include "keymask.h"

#include <array>
#include <cstddef>
#include <cstdint>

class KeyMatrix
{
public:
    static void setup();
    
public:
    constexpr KeyMatrix(const int      addr,
                        const uint16_t rowMask,
                        const uint16_t colMask);

public:
    void init();
    void scan();
    
    const KeyMask& state() const;
        
private:
    const int      mAddr;
    const uint16_t mRowMask;
    const uint16_t mColMask;

    KeyMask mState;
    
private:
    KeyMatrix(const KeyMatrix&) = delete;
    KeyMatrix& operator=(const KeyMatrix&) = delete;
};


inline
constexpr KeyMatrix::KeyMatrix(const int      addr,
                               const uint16_t rowMask,
                               const uint16_t colMask)
    : mAddr(addr)
    , mRowMask(rowMask)
    , mColMask(colMask)
    , mState()
{ }

inline
const KeyMask& KeyMatrix::state() const
{
    return mState;
}

#endif
