#ifndef INCLUDED_BITMASK2D_H
#define INCLUDED_BITMASK2D_H

#include "types/bitmask.h"

#include <array>
#include <cstddef>
#include <cstdint>

template <std::size_t Columns, std::size_t Rows>
class Bitmask2d
{
public:
    static constexpr std::size_t kColumns = Columns;
    static constexpr std::size_t kRows    = Rows;

public:
    typedef Bitmask<Columns> Row;
    
private:
    typedef std::array<Row, Rows> RowData;
    
public:
    typedef typename RowData::const_iterator const_iterator;
    typedef typename RowData::iterator       iterator;

public:
    constexpr Bitmask2d() = default;

public:
    bool empty() const;
    void clear();

public:
    const_iterator begin() const;
    const_iterator end() const;
    iterator begin();
    iterator end();
    
public:
    const Row& operator[](const std::size_t n) const;
    Row& operator[](const std::size_t n);

    void operator|=(const Bitmask2d<Columns, Rows>& rhs);
    void operator&=(const Bitmask2d<Columns, Rows>& rhs);
    void operator^=(const Bitmask2d<Columns, Rows>& rhs);

private:
    RowData mRowData;
};


template <std::size_t Columns, std::size_t Rows>
inline
bool Bitmask2d<Columns, Rows>::empty() const
{
    for (const auto& row : mRowData)
    {
        if (!row.empty())
        {
            return false;
        }
    }

    return true;
}

template <std::size_t Columns, std::size_t Rows>
inline
void Bitmask2d<Columns, Rows>::clear()
{
    for (auto& row : mRowData)
    {
        row.clear();
    }
}

template <std::size_t Columns, std::size_t Rows>
inline
const typename Bitmask2d<Columns, Rows>::Row& Bitmask2d<Columns, Rows>::operator[](const std::size_t n) const
{
    return mRowData[n];
}

template <std::size_t Columns, std::size_t Rows>
inline
typename Bitmask2d<Columns, Rows>::Row& Bitmask2d<Columns, Rows>::operator[](const std::size_t n)
{
    return mRowData[n];
}

template <std::size_t Columns, std::size_t Rows>
inline
void Bitmask2d<Columns, Rows>::operator|=(const Bitmask2d<Columns, Rows>& rhs)
{
    for (size_t i(0); i < Rows; ++i)
    {
        mRowData[i] |= rhs.mRowData[i];
    }
}

template <std::size_t Columns, std::size_t Rows>
inline
void Bitmask2d<Columns, Rows>::operator&=(const Bitmask2d<Columns, Rows>& rhs)
{
    for (size_t i(0); i < Rows; ++i)
    {
        mRowData[i] &= rhs.mRowData[i];
    }
}

template <std::size_t Columns, std::size_t Rows>
inline
void Bitmask2d<Columns, Rows>::operator^=(const Bitmask2d<Columns, Rows>& rhs)
{
    for (size_t i(0); i < Rows; ++i)
    {
        mRowData[i] ^= rhs.mRowData[i];
    }
}

template <std::size_t Columns, std::size_t Rows>
inline
typename Bitmask2d<Columns, Rows>::const_iterator Bitmask2d<Columns, Rows>::begin() const
{
    return mRowData.begin();
}

template <std::size_t Columns, std::size_t Rows>
inline
typename Bitmask2d<Columns, Rows>::const_iterator Bitmask2d<Columns, Rows>::end() const
{
    return mRowData.end();
}

template <std::size_t Columns, std::size_t Rows>
inline
typename Bitmask2d<Columns, Rows>::iterator Bitmask2d<Columns, Rows>::begin()
{
    return mRowData.begin();
}

template <std::size_t Columns, std::size_t Rows>
inline
typename Bitmask2d<Columns, Rows>::iterator Bitmask2d<Columns, Rows>::end()
{
    return mRowData.end();
}

#endif
