#include "keymap.h"

KeyMap::KeyMap(std::initializer_list<ColumnData> rows)
    : mData()
{
    size_t n(0);

    for (const auto& row : rows)
    {
        mData[n++] = row; 
    }
}
