#ifndef INCLUDED_KEYMAP_H
#define INCLUDED_KEYMAP_H

#include <array>
#include <initializer_list>

#include <stdio.h>
#include <inttypes.h>

class KeyMap
{
public:
    static const int Rows    = 5;
    static const int Columns = 16;

public:
    typedef std::array<uint32_t, Columns> ColumnData;
    typedef std::array<ColumnData, Rows> RowData;

public:
    explicit KeyMap(std::initializer_list<ColumnData> rows);

public:
    const ColumnData& operator[](size_t n) const;
    
private:
    RowData mData;

private:
    KeyMap(const KeyMap&) = delete;
    KeyMap& operator=(const KeyMap&) = delete;
};

inline
const KeyMap::ColumnData& KeyMap::operator[](size_t n) const
{
    return mData[n];
}

#endif
