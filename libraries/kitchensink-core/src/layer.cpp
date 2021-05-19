#include "layer.h"

Event Layer::at(int row, int column) const
{
    if (row >= 0 && row < (int)kRows &&
        column >= 0 && column < (int)kColumns)
    {
        return mapping[row][column];
    }
    else
    {
        return Event();
    }
}

void Layer::set(int row, int column, const Event& event)
{
    if (row >= 0 && row < (int)kRows &&
        column >= 0 && column < (int)kColumns)
    {
        mapping[row][column] = event;
    }
}

void Layer::clear()
{
    name.clear();

    for (auto& row : mapping)
    {
        row.fill(Event());
    }
}
