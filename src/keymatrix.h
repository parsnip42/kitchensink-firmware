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
    typedef Bitmask2d<10, 5> Mask;

public:
    class Event
    {
    public:
        Event(int  nRow,
              int  nColumn,
              bool nPressed);
        
    public:
        int  row;
        int  column;
        bool pressed;
    };

    typedef std::function<void(const Event&)> EventCallback;
    
public:
    KeyMatrix(int addr, uint16_t rowMask, uint16_t colMask);

public:
    void scan(const EventCallback& callback);

    const Mask::Row& operator[](std::size_t n) const;
    const Mask& delta() const;
    
private:
    void init();
    
private:
    const int      mAddr;
    const uint16_t mRowMask;
    const uint16_t mColMask;

    Mask mMask;
    Mask mDelta;
    
private:
    KeyMatrix(const KeyMatrix&) = delete;
    KeyMatrix& operator=(const KeyMatrix&) = delete;
};


inline
KeyMatrix::Event::Event(int  nRow,
                        int  nColumn,
                        bool nPressed)
    : row(nRow)
    , column(nColumn)
    , pressed(nPressed)
{ }

inline
const KeyMatrix::Mask::Row& KeyMatrix::operator[](std::size_t n) const
{
    return mMask[n];
}

inline
const KeyMatrix::Mask& KeyMatrix::delta() const
{
    return mDelta;
}

#endif
