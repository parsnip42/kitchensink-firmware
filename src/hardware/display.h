#ifndef INCLUDED_DISPLAY_H
#define INCLUDED_DISPLAY_H

#include "types/mutabledataref.h"

#include <cstdint>

class Display
{
public:
    Display() = default;
    virtual ~Display() = default;

public:
    virtual void clear() = 0;
    virtual int width() const = 0;
    virtual int height() const = 0;
    virtual MutableDataRef rasterLine() = 0;
    virtual void rasterize(int row) = 0;
};

#endif
