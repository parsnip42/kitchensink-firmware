#ifndef INCLUDED_KEYLOCATION_H
#define INCLUDED_KEYLOCATION_H

class KeyLocation
{
public:
    constexpr KeyLocation();

public:
    int row;
    int column;
    int layer;
};


inline
constexpr KeyLocation::KeyLocation()
    : row(0)
    , column(0)
    , layer(0)
{ }

#endif
