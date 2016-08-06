#ifndef INCLUDED_BITMASK_H
#define INCLUDED_BITMASK_H

#include "bitmaskattributes.h"

#include <cstddef>
#include <cstdint>

template <std::size_t Size>
class Bitmask
{
public:
    typedef typename BitmaskAttributes<Size>::Data Data;
    
public:
    Bitmask();
    
public:
    bool operator[](std::size_t n) const;
    std::size_t size() const;
    const Data& data() const;
    Data& data();
    
private:
    Data mData;
};


template <std::size_t Size>
inline
Bitmask<Size>::Bitmask()
    : mData(0)
{ }

template <std::size_t Size>
inline
bool Bitmask<Size>::operator[](std::size_t n) const
{
    return (mData >> n) & 1;
}

template <std::size_t Size>
inline
std::size_t Bitmask<Size>::size() const
{
    return Size;
}

template <std::size_t Size>
inline
const typename Bitmask<Size>::Data& Bitmask<Size>::data() const
{
    return mData;
}

template <std::size_t Size>
inline
typename Bitmask<Size>::Data& Bitmask<Size>::data()
{
    return mData;
}

#endif
