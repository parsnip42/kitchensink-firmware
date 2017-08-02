#ifndef INCLUDED_DIMENSION_H
#define INCLUDED_DIMENSION_H

class Dimension
{
public:
    constexpr Dimension();

    constexpr Dimension(int nWidth,
              int nHeight);
    
public:
    int width;
    int height;
};


inline
constexpr Dimension::Dimension()
    : width(0)
    , height(0)
{ }

inline
constexpr Dimension::Dimension(int nWidth,
                               int nHeight)
    : width(nWidth)
    , height(nHeight)
{ }

#endif
