#ifndef INCLUDED_BITMASK2D_H
#define INCLUDED_BITMASK2D_H

#include "bitmask.h"

#include <array>
#include <cstddef>
#include <cstdint>

template <std::size_t Width, std::size_t Height>
class Bitmask2d
{
public:
    typedef Bitmask<Width> Row;
    
public:
    Bitmask2d();

public:
    std::size_t size() const;
    bool empty() const;

public:
    const Row& operator[](std::size_t n) const;
    Row& operator[](std::size_t n);

    void operator|=(const Bitmask2d<Width, Height>& rhs);
    void operator&=(const Bitmask2d<Width, Height>& rhs);
    void operator^=(const Bitmask2d<Width, Height>& rhs);

private:
    typedef std::array<Row, Height> Rows;

    Rows mRows;

public:
    typedef typename Rows::const_iterator const_iterator;
    typedef typename Rows::iterator       iterator;

    const_iterator begin() const;
    const_iterator end() const;
    iterator begin();
    iterator end();
};


template <std::size_t Width, std::size_t Height>
inline
Bitmask2d<Width, Height>::Bitmask2d()
    : mRows()
{ }

template <std::size_t Width, std::size_t Height>
inline
std::size_t Bitmask2d<Width, Height>::size() const
{
    return Height;
}

template <std::size_t Width, std::size_t Height>
inline
bool Bitmask2d<Width, Height>::empty() const
{
    for (const auto& row : mRows)
    {
        if (!row.empty())
        {
            return false;
        }
    }

    return true;
}

template <std::size_t Width, std::size_t Height>
inline
const typename Bitmask2d<Width, Height>::Row& Bitmask2d<Width, Height>::operator[](std::size_t n) const
{
    return mRows[n];
}

template <std::size_t Width, std::size_t Height>
inline
typename Bitmask2d<Width, Height>::Row& Bitmask2d<Width, Height>::operator[](std::size_t n)
{
    return mRows[n];
}

template <std::size_t Width, std::size_t Height>
inline
void Bitmask2d<Width, Height>::operator|=(const Bitmask2d<Width, Height>& rhs)
{
    for (size_t i(0); i < Height; ++i)
    {
        mRows[i] |= rhs.mRows[i];
    }
}

template <std::size_t Width, std::size_t Height>
inline
void Bitmask2d<Width, Height>::operator&=(const Bitmask2d<Width, Height>& rhs)
{
    for (size_t i(0); i < Height; ++i)
    {
        mRows[i] &= rhs.mRows[i];
    }
}

template <std::size_t Width, std::size_t Height>
inline
void Bitmask2d<Width, Height>::operator^=(const Bitmask2d<Width, Height>& rhs)
{
    for (size_t i(0); i < Height; ++i)
    {
        mRows[i] ^= rhs.mRows[i];
    }
}

template <std::size_t Width, std::size_t Height>
inline
typename Bitmask2d<Width, Height>::const_iterator Bitmask2d<Width, Height>::begin() const
{
    return mRows.begin();
}

template <std::size_t Width, std::size_t Height>
inline
typename Bitmask2d<Width, Height>::const_iterator Bitmask2d<Width, Height>::end() const
{
    return mRows.end();
}

template <std::size_t Width, std::size_t Height>
inline
typename Bitmask2d<Width, Height>::iterator Bitmask2d<Width, Height>::begin()
{
    return mRows.begin();
}

template <std::size_t Width, std::size_t Height>
inline
typename Bitmask2d<Width, Height>::iterator Bitmask2d<Width, Height>::end()
{
    return mRows.end();
}

#endif
