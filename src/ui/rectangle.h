#ifndef INCLUDED_RECTANGLE_H
#define INCLUDED_RECTANGLE_H

#include "ui/dimension.h"

class Rectangle
{
public:
    Rectangle();

    Rectangle(int nX,
              int nY,
              int nWidth,
              int nHeight);

    explicit Rectangle(const Dimension& dimension);

public:
    Rectangle offsetX(int offset) const;
    Rectangle offsetY(int offset) const;
    
public:
    int x;
    int y;
    int width;
    int height;
};


inline
Rectangle::Rectangle()
    : x(0)
    , y(0)
    , width(0)
    , height(0)
{ }

inline
Rectangle::Rectangle(int nX,
                     int nY,
                     int nWidth,
                     int nHeight)
    : x(nX)
    , y(nY)
    , width(nWidth)
    , height(nHeight)
{ }

inline
Rectangle::Rectangle(const Dimension& dimension)
    : x(0)
    , y(0)
    , width(dimension.width)
    , height(dimension.height)
{ }

inline
Rectangle Rectangle::offsetX(int offset) const
{
    auto rect(*this);

    rect.x += offset;

    return rect;
}

inline
Rectangle Rectangle::offsetY(int offset) const
{
    auto rect(*this);

    rect.y += offset;

    return rect;
}

#endif
