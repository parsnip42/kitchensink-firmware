#include "keymap.h"

KeyMap::KeyMap(std::initializer_list<Row> rows)
    : rows_()
{
    size_t n(0);

    for (const auto& row : rows)
    {
        rows_[n++] = row; 
    }
}
