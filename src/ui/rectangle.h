#ifndef INCLUDED_RECTANGLE_H
#define INCLUDED_RECTANGLE_H

class Rectangle
{
public:
    Rectangle(int nX,
              int nY,
              int nWidth,
              int nHeight);
    
public:
    int x;
    int y;
    int width;
    int height;
};


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

#endif /* INCLUDED_RECTANGLE_H */
