#ifndef INCLUDED_BITMASK2D_H
#define INCLUDED_BITMASK2D_H

#include "types/bitmask.h"

#include <array>
#include <cstddef>
#include <cstdint>

template <std::size_t Width, std::size_t Height>
class Bitmask2d
{
public:
    static constexpr std::size_t kRows    = Height;
    static constexpr std::size_t kColumns = Width;

public:
    typedef Bitmask<Width> Row;
    
public:
    constexpr Bitmask2d() = default;

public:
    bool empty() const;

public:
    const Row& operator[](const std::size_t n) const;
    Row& operator[](const std::size_t n);

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
const typename Bitmask2d<Width, Height>::Row& Bitmask2d<Width, Height>::operator[](const std::size_t n) const
{
    return mRows[n];
}

template <std::size_t Width, std::size_t Height>
inline
typename Bitmask2d<Width, Height>::Row& Bitmask2d<Width, Height>::operator[](const std::size_t n)
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
