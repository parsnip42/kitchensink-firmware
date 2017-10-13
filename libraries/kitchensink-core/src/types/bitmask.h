#ifndef INCLUDED_BITMASK_H
#define INCLUDED_BITMASK_H

#include "types/bitmaskattributes.h"
#include "types/bititerator.h"

#include <cstddef>
#include <cstdint>

template <std::size_t Size>
class Bitmask
{
public:
    typedef typename BitmaskAttributes<Size>::Data Data;

public:
    class reference
    {
    private:
        constexpr reference(Data&       data,
                            std::size_t bit);

    public:
        constexpr operator bool() const;
        reference& operator=(bool state);
        
    private:
        Data&       mData;
        std::size_t mBit;

    private:
        friend class Bitmask;
    };
    
public:
    constexpr Bitmask();
    explicit constexpr Bitmask(const Data& data);
    
public:
    constexpr std::size_t size() const;
    constexpr bool empty() const;
    BitIterator<Data> bitIterator() const;
    void clear();
    
public:
    constexpr bool operator[](std::size_t n) const;
    reference operator[](std::size_t n);

    void operator=(const Data& data);

    void operator|=(const Bitmask<Size>& rhs);
    void operator&=(const Bitmask<Size>& rhs);
    void operator^=(const Bitmask<Size>& rhs);

    void operator|=(const Data& data);
    void operator&=(const Data& data);
    void operator^=(const Data& data);

private:
    Data mData;

private:
    template <std::size_t Size_>
    friend bool operator==(const Bitmask<Size_>& lhs,
                           const Bitmask<Size_>& rhs);

    template <std::size_t Size_>
    friend bool operator==(const Bitmask<Size_>&                lhs,
                           const typename Bitmask<Size_>::Data& rhs);
};


template <std::size_t Size>
inline
bool operator==(const Bitmask<Size>& lhs,
                const Bitmask<Size>& rhs)
{
    return (lhs.mData == rhs.mData);
}

template <std::size_t Size>
inline
bool operator!=(const Bitmask<Size>& lhs,
                const Bitmask<Size>& rhs)
{
    return !(lhs == rhs);
}

template <std::size_t Size>
inline
bool operator==(const Bitmask<Size>&                lhs,
                const typename Bitmask<Size>::Data& rhs)
{
    return (lhs.mData == rhs);
}

template <std::size_t Size>
inline
bool operator!=(const Bitmask<Size>&                lhs,
                const typename Bitmask<Size>::Data& rhs)
{
    return !(lhs == rhs);
}


template <std::size_t Size>
inline
constexpr Bitmask<Size>::reference::reference(Data&       data,
                                              std::size_t bit)
    : mData(data)
    , mBit(bit)
{ }

template <std::size_t Size>
inline
constexpr Bitmask<Size>::reference::operator bool() const
{
    return (mData >> mBit) & 1;
}

template <std::size_t Size>
inline
typename Bitmask<Size>::reference& Bitmask<Size>::reference::operator=(bool state)
{
    auto mask(Data(1) << mBit);
              
    mData = (mData & ~mask) | (-state & mask);

    return *this;
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
constexpr std::size_t Bitmask<Size>::size() const
{
    return Size;
}

template <std::size_t Size>
inline
constexpr bool Bitmask<Size>::empty() const
{
    return mData == 0;
}

template <std::size_t Size>
inline
BitIterator<typename Bitmask<Size>::Data> Bitmask<Size>::bitIterator() const
{
    return BitIterator<Data>(mData);
}

template <std::size_t Size>
inline
void Bitmask<Size>::clear()
{
    mData = 0;
}

template <std::size_t Size>
inline
constexpr bool Bitmask<Size>::operator[](const std::size_t n) const
{
    return (mData >> n) & 1;
}

template <std::size_t Size>
inline
typename Bitmask<Size>::reference Bitmask<Size>::operator[](const std::size_t n)
{
    return reference(mData, n);
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

#endif







