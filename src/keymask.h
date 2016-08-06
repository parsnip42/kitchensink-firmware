#ifndef INCLUDED_KEYMASK_H
#define INCLUDED_KEYMASK_H

#include "bitmask.h"

#include <array>

#include <stdio.h>
#include <inttypes.h>

template <size_t RowCount>
class KeyMask
{
public:
    typedef Bitmask<10> Row;
    
public:
    KeyMask();

public:
    const Row& operator[](size_t n) const;
    Row& operator[](size_t n);
    size_t size() const;
    
private:
    std::array<Row, RowCount> mRows;
    
private:
    KeyMask(const KeyMask&) = delete;
    KeyMask& operator=(const KeyMask&) = delete;
};


template <size_t RowCount>
inline
KeyMask<RowCount>::KeyMask()
    : mRows()
{ }

template <size_t RowCount>
inline
const typename KeyMask<RowCount>::Row& KeyMask<RowCount>::operator[](size_t n) const
{
    return mRows[n];
}

template <size_t RowCount>
inline
typename KeyMask<RowCount>::Row& KeyMask<RowCount>::operator[](size_t n)
{
    return mRows[n];
}

template <size_t RowCount>
inline
size_t KeyMask<RowCount>::size() const
{
    return RowCount;
}

#endif
