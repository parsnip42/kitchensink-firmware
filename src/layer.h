#ifndef INCLUDED_LAYER_H
#define INCLUDED_LAYER_H

#include "keyid.h"

class Layer
{
public:
    static const int Rows    = 5;
    static const int Columns = 20;
    
public:
    explicit Layer(const KeyId (&mapping)[Rows][Columns]);

public:
    KeyId at(int row, int column) const;
    
private:
    const KeyId (&mMapping)[Rows][Columns];
};


inline
Layer::Layer(const KeyId (&mapping)[Rows][Columns])
    : mMapping(mapping)
{ }

inline
KeyId Layer::at(int row, int column) const
{
    if ((row >= 0) && (row < Rows)
        && (column >= 0) && (column < Columns))
    {
        return mMapping[row][column];
    }
    else
    {
        return 0;
    }
}

#endif
