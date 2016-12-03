#ifndef INCLUDED_LAYER_H
#define INCLUDED_LAYER_H

#include "keyid.h"

#include <array>
#include <initializer_list>

class Layer
{
public:
    static constexpr int kRows    = 5;
    static constexpr int kColumns = 20;
    
public:
    constexpr Layer();
    explicit Layer(const char* name,
                   const std::initializer_list<std::initializer_list<KeyId>>& list);

public:
    const char* name() const;
    KeyId at(int row, int column) const;
    
private:
    const char*                                    mName;
    std::array<std::array<KeyId, kColumns>, kRows> mMapping;
};

inline
constexpr Layer::Layer()
    : mName("")
{ }

inline
const char* Layer::name() const
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
