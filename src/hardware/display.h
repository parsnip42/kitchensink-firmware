#ifndef INCLUDED_DISPLAY_H
#define INCLUDED_DISPLAY_H

#include "types/mutabledataref.h"

#include <array>
#include <cstdint>

class Display
{
private:
    static constexpr int kWidth  = 240;
    static constexpr int kHeight = 64;
    
public:
    Display();

public:
    void init();
    void clear();
    int width() const;
    int height() const;
    
    MutableDataRef rasterLine();
    void rasterize(int row);
    
private:
    void initRegion(int x, int y, int w, int h);
    void writeInst(uint8_t data);
    void writeData(uint8_t data);

private:
    std::array<uint8_t, kWidth> mRasterBuf;
    
private:
    Display(const Display&) = delete;
    Display& operator=(const Display&) = delete;
};


inline
int Display::width() const
{
    return kWidth;
}

inline
int Display::height() const
{
    return kHeight;
}

#endif
