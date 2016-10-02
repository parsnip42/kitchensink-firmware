#ifndef INCLUDED_LAYER_H
#define INCLUDED_LAYER_H

#include "keyid.h"

#include <array>
#include <initializer_list>

class Layer
{
public:
    static const int kRows    = 5;
    static const int kColumns = 20;
    
public:
    // explicit Layer(const KeyId list[5][20]);
    explicit Layer(const std::initializer_list<std::initializer_list<KeyId>>& list);

public:
    KeyId at(int row, int column) const;
    
private:
    std::array<std::array<KeyId, kColumns>, kRows> mMapping;

private:
    Layer(const Layer&) = delete;
    Layer& operator=(const Layer&) = delete;
};


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
