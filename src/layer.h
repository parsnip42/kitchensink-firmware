#ifndef INCLUDED_LAYER_H
#define INCLUDED_LAYER_H

#include "keyid.h"
#include "types/strbuf.h"
#include "types/strref.h"

#include <array>
#include <initializer_list>

class Layer
{
public:
    static constexpr int kRows    = 5;
    static constexpr int kColumns = 20;

public:
    typedef std::array<KeyId, kColumns> Row;
    typedef std::array<Row, kRows>      Mapping;
    
public:
    constexpr Layer() = default;

public:
    KeyId at(int row, int column) const;
    
public:
    Types::StrBuf<12> name;
    Mapping           mapping;
};

inline
KeyId Layer::at(int row, int column) const
{
    if ((row >= 0) && (row < kRows)
        && (column >= 0) && (column < kColumns))
    {
        return mapping[row][column];
    }
    else
    {
        return KeyId();
    }
}

#endif
