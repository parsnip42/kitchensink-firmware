#ifndef INCLUDED_LAYER_H
#define INCLUDED_LAYER_H

#include "keyid.h"
#include "types/strbuf.h"
#include "config.h"

#include <array>

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
    void clear();
    
public:
    StrBuf<Config::kLayerNameLen> name;
    Mapping                       mapping;
};

#endif
