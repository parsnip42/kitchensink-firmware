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
    constexpr Bitmask();
    explicit constexpr Bitmask(const Data& data);
    
public:
    bool empty() const;
    void set(const std::size_t n);
    void clear(const std::size_t n);
    
public:
    bool operator[](std::size_t n) const;

    void operator=(const Data& data);

    void operator|=(const Bitmask<Size>& rhs);
    void operator&=(const Bitmask<Size>& rhs);
    void operator^=(const Bitmask<Size>& rhs);

    void operator|=(const Data& data);
    void operator&=(const Data& data);
    void operator^=(const Data& data);

    void operator>>=(const std::size_t n);

private:
    Data mData;
};


template <std::size_t Size>
inline
bool operator==(const Bitmask<Size>& lhs, const Bitmask<Size>& rhs)
{
    return (lhs.data() == rhs.data());
}

template <std::size_t Size>
inline
bool operator!=(const Bitmask<Size>& lhs, const Bitmask<Size>& rhs)
{
    return !(lhs == rhs);
}


template <std::size_t Size>
inline
constexpr Bitmask<Size>::Bitmask()
    : mData(0)
{ }

template <std::size_t Size>
inline
constexpr Bitmask<Size>::Bitmask(const Data& data)
    : mData(data)
{ }

template <std::size_t Size>
inline
bool Bitmask<Size>::empty() const
{
    return (mData == 0);
}

template <std::size_t Size>
inline
void Bitmask<Size>::set(const std::size_t n)
{
    mData |= (Data)1 << n;
}

template <std::size_t Size>
inline
void Bitmask<Size>::clear(const std::size_t n)
{
    mData &= ~((Data)1 << n);
}

template <std::size_t Size>
inline
bool Bitmask<Size>::operator[](const std::size_t n) const
{
    return (mData >> n) & 1;
}

template <std::size_t Size>
inline
void Bitmask<Size>::operator=(const Data& data)
{
    mData = data;
}

template <std::size_t Size>
inline
void Bitmask<Size>::operator|=(const Bitmask<Size>& rhs)
{
    mData |= rhs.mData;
}

template <std::size_t Size>
inline
void Bitmask<Size>::operator&=(const Bitmask<Size>& rhs)
{
    mData &= rhs.mData;
}

template <std::size_t Size>
inline
void Bitmask<Size>::operator^=(const Bitmask<Size>& rhs)
{
    mData ^= rhs.mData;
}

template <std::size_t Size>
inline
void Bitmask<Size>::operator|=(const Data& data)
{
    mData |= data;
}

template <std::size_t Size>
inline
void Bitmask<Size>::operator&=(const Data& data)
{
    mData &= data;
}

template <std::size_t Size>
inline
void Bitmask<Size>::operator^=(const Data& data)
{
    mData ^= data;
}

template <std::size_t Size>
inline
void Bitmask<Size>::operator>>=(const std::size_t n)
{
    mData >>= n;
}

#endif
