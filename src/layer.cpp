#include "layer.h"

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

void Layer::clear()
{
    name.clear();

    for (auto& row : mapping)
    {
        row.fill(KeyId());
    }
}
