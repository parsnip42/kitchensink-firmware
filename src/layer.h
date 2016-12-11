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
    constexpr Layer() = default;
    explicit Layer(const Types::StrRef&                                       name,
                   const std::initializer_list<std::initializer_list<KeyId>>& list);

public:
    Types::StrRef name() const;
    KeyId at(int row, int column) const;
    
private:
    Types::StrBuf<12>                              mName;
    std::array<std::array<KeyId, kColumns>, kRows> mMapping;
};

inline
Types::StrRef Layer::name() const
{
    return mName;
}

inline
KeyId Layer::at(int row, int column) const
{
    if ((row >= 0) && (row < kRows)
        && (column >= 0) && (column < kColumns))
    {
        return mMapping[row][column];
    }
    else
    {
        return KeyId::None;
    }
}

#endif
