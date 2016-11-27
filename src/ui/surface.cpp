#include "surface.h"
#include "display.h"

#include <cstring>

namespace UI
{

namespace
{
constexpr uint8_t charset[] =
{
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x24,0x00,0x10,0x00,0x00,
    0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x08,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x62,0x10,0x24,0x24,0x10,0x64,0x18,0x10,0x08,0x20,0x00,0x00,0x00,
    0x00,0x00,0x04,0x3c,0x08,0x3c,0x3c,0x02,0x7e,0x1c,0x7e,0x3c,0x3c,0x00,0x00,0x00,0x00,0x00,0x3c,0x7c,
    0x3c,0x7c,0x3c,0x78,0x7e,0x7e,0x3c,0x42,0x38,0x0e,0x42,0x40,0x82,0x42,0x3c,0x7c,0x3c,0x7c,0x3c,0xfe,
    0x42,0x42,0x82,0x42,0x82,0x7e,0x38,0x40,0x38,0x28,0x00,0x00,0x00,0x40,0x00,0x02,0x00,0x0e,0x00,0x40,
    0x10,0x04,0x40,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x0c,0x10,
    0x30,0x92,0x10,0x24,0x24,0x7c,0x94,0x24,0x10,0x10,0x10,0x00,0x00,0x00,0x00,0x00,0x04,0x42,0x18,0x42,
    0x42,0x06,0x40,0x20,0x02,0x42,0x42,0x00,0x00,0x04,0x00,0x40,0x42,0x82,0x42,0x42,0x42,0x44,0x40,0x40,
    0x42,0x42,0x10,0x04,0x44,0x40,0xc6,0x42,0x42,0x42,0x42,0x42,0x42,0x10,0x42,0x42,0x82,0x42,0x82,0x02,
    0x20,0x40,0x08,0x44,0x00,0x00,0x00,0x40,0x00,0x02,0x00,0x10,0x00,0x40,0x10,0x04,0x40,0x10,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x08,0x8c,0x10,0x00,0x24,0x92,
    0x68,0x24,0x00,0x20,0x08,0x00,0x00,0x00,0x00,0x00,0x08,0x42,0x28,0x42,0x42,0x0a,0x40,0x40,0x02,0x42,
    0x42,0x00,0x00,0x08,0x00,0x20,0x42,0x9e,0x42,0x42,0x42,0x42,0x40,0x40,0x42,0x42,0x10,0x04,0x48,0x40,
    0xaa,0x42,0x42,0x42,0x42,0x42,0x40,0x10,0x42,0x42,0x82,0x24,0x44,0x02,0x20,0x20,0x08,0x00,0x00,0x00,
    0x00,0x40,0x00,0x02,0x00,0x10,0x00,0x40,0x00,0x00,0x40,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,
    0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x08,0x00,0x10,0x00,0x7e,0x90,0x08,0x18,0x00,0x20,0x08,0x24,
    0x10,0x00,0x00,0x00,0x08,0x46,0x08,0x02,0x02,0x12,0x40,0x40,0x04,0x42,0x42,0x10,0x10,0x10,0x7e,0x10,
    0x42,0xa2,0x42,0x42,0x40,0x42,0x40,0x40,0x40,0x42,0x10,0x04,0x50,0x40,0x92,0x62,0x42,0x42,0x42,0x42,
    0x40,0x10,0x42,0x42,0x82,0x24,0x44,0x04,0x20,0x20,0x08,0x00,0x00,0x00,0x3c,0x7c,0x3c,0x3e,0x3c,0x7c,
    0x3e,0x7c,0x30,0x0c,0x42,0x10,0xfc,0x7c,0x3c,0x7c,0x3e,0x5e,0x3e,0x7c,0x42,0x42,0x82,0x42,0x42,0x7e,
    0x10,0x10,0x08,0x00,0x10,0x00,0x24,0x90,0x10,0x30,0x00,0x20,0x08,0x18,0x10,0x00,0x00,0x00,0x10,0x4a,
    0x08,0x04,0x1c,0x22,0x7c,0x7c,0x04,0x3c,0x42,0x10,0x10,0x20,0x00,0x08,0x04,0xa2,0x42,0x7c,0x40,0x42,
    0x78,0x78,0x40,0x7e,0x10,0x04,0x60,0x40,0x92,0x52,0x42,0x42,0x42,0x42,0x3c,0x10,0x42,0x42,0x82,0x18,
    0x28,0x08,0x20,0x10,0x08,0x00,0x00,0x00,0x02,0x42,0x42,0x42,0x42,0x10,0x42,0x42,0x10,0x04,0x44,0x10,
    0x92,0x42,0x42,0x42,0x42,0x60,0x40,0x10,0x42,0x42,0x82,0x42,0x42,0x04,0x20,0x10,0x04,0x00,0x10,0x00,
    0x24,0x7c,0x10,0x4a,0x00,0x20,0x08,0x7e,0x7c,0x00,0x7e,0x00,0x10,0x52,0x08,0x08,0x02,0x42,0x02,0x42,
    0x08,0x42,0x3e,0x00,0x00,0x40,0x00,0x04,0x08,0xa2,0x7e,0x42,0x40,0x42,0x40,0x40,0x4e,0x42,0x10,0x04,
    0x60,0x40,0x82,0x4a,0x42,0x7c,0x42,0x7c,0x02,0x10,0x42,0x24,0x92,0x18,0x10,0x10,0x20,0x10,0x08,0x00,
    0x00,0x00,0x3e,0x42,0x40,0x42,0x42,0x10,0x42,0x42,0x10,0x04,0x48,0x10,0x92,0x42,0x42,0x42,0x42,0x40,
    0x40,0x10,0x42,0x42,0x92,0x24,0x42,0x08,0x10,0x10,0x08,0x00,0x10,0x00,0x7e,0x12,0x20,0x44,0x00,0x20,
    0x08,0x18,0x10,0x00,0x00,0x00,0x20,0x62,0x08,0x10,0x02,0x7e,0x02,0x42,0x08,0x42,0x02,0x00,0x00,0x20,
    0x7e,0x08,0x08,0xa6,0x42,0x42,0x40,0x42,0x40,0x40,0x42,0x42,0x10,0x04,0x50,0x40,0x82,0x46,0x42,0x40,
    0x42,0x50,0x02,0x10,0x42,0x24,0x92,0x24,0x10,0x20,0x20,0x08,0x08,0x00,0x00,0x00,0x42,0x42,0x40,0x42,
    0x7e,0x10,0x42,0x42,0x10,0x04,0x70,0x10,0x92,0x42,0x42,0x42,0x42,0x40,0x3c,0x10,0x42,0x24,0x92,0x18,
    0x42,0x10,0x10,0x10,0x08,0x00,0x00,0x00,0x24,0x12,0x2c,0x44,0x00,0x20,0x08,0x24,0x10,0x00,0x00,0x00,
    0x20,0x42,0x08,0x20,0x42,0x02,0x02,0x42,0x10,0x42,0x02,0x00,0x00,0x10,0x00,0x10,0x00,0x9a,0x42,0x42,
    0x42,0x42,0x40,0x40,0x42,0x42,0x10,0x44,0x48,0x40,0x82,0x42,0x42,0x40,0x42,0x48,0x42,0x10,0x42,0x24,
    0xaa,0x24,0x10,0x40,0x20,0x08,0x08,0x00,0x00,0x00,0x42,0x42,0x40,0x42,0x40,0x10,0x42,0x42,0x10,0x04,
    0x48,0x10,0x92,0x42,0x42,0x42,0x42,0x40,0x02,0x10,0x42,0x24,0x92,0x24,0x42,0x20,0x10,0x10,0x08,0x00,
    0x10,0x00,0x24,0x92,0x52,0x44,0x00,0x10,0x10,0x00,0x00,0x10,0x00,0x10,0x40,0x42,0x08,0x40,0x42,0x02,
    0x42,0x42,0x10,0x42,0x04,0x10,0x10,0x08,0x00,0x20,0x08,0x80,0x42,0x42,0x42,0x44,0x40,0x40,0x42,0x42,
    0x10,0x44,0x44,0x40,0x82,0x42,0x42,0x40,0x4a,0x44,0x42,0x10,0x42,0x18,0xc6,0x42,0x10,0x40,0x20,0x04,
    0x08,0x00,0x00,0x00,0x42,0x42,0x42,0x42,0x40,0x10,0x42,0x42,0x10,0x04,0x44,0x10,0x92,0x42,0x42,0x42,
    0x42,0x40,0x02,0x10,0x42,0x18,0x92,0x42,0x42,0x40,0x10,0x10,0x08,0x00,0x10,0x00,0x24,0x7c,0x4c,0x3a,
    0x00,0x08,0x20,0x00,0x00,0x10,0x00,0x10,0x40,0x3c,0x3e,0x7e,0x3c,0x02,0x3c,0x3c,0x10,0x3c,0x38,0x10,
    0x10,0x04,0x00,0x40,0x08,0x7e,0x42,0x7c,0x3c,0x78,0x7e,0x40,0x3c,0x42,0x38,0x38,0x42,0x7e,0x82,0x42,
    0x3c,0x40,0x3c,0x42,0x3c,0x10,0x3c,0x18,0x82,0x42,0x10,0x7e,0x38,0x04,0x38,0x00,0x00,0x00,0x3e,0x7c,
    0x3c,0x3e,0x3c,0x10,0x3e,0x42,0x38,0x44,0x42,0x38,0x92,0x42,0x3c,0x7c,0x3e,0x40,0x7c,0x0e,0x3e,0x18,
    0x7c,0x42,0x3e,0x7e,0x0c,0x10,0x30,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,
    0x00,0x44,0x00,0x00,0x00,0x00,0x00,0x40,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3c,0x00,0x00,0x38,0x00,0x00,0x00,0x00,
    0x00,0x40,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3c,0x00,0x00,0x00,0x00,0x00
};

constexpr int kCharsetCount = 94;
}

Surface::Surface(Display& display)
    : mDisplay(display)
{ }

void Surface::paintText(int         x,
                        int         y,
                        const char* str,
                        uint8_t     fg,
                        uint8_t     bg)
{
    constexpr int kCharHeight(14);
    
    auto len(std::strlen(str));
    
    initRegion(x, y, len << 3, kCharHeight);

    const ColorMap colorMap(fg, bg);
    
    for (int line(0); line < kCharHeight; ++line)
    {
        paintTextLine(str, str + len, line, colorMap);
    }
}

void Surface::initRegion(int x, int y, int w, int h)
{
    mDisplay.initRegion(x, y, w, h);
}

void Surface::paintTextLine(const char*     begin,
                            const char*     end,
                            const int       line,
                            const ColorMap& colorMap)
{
    for (auto it(begin); it != end; ++it)
    {
        const auto chr(*it);
        
        if (chr > 32 && chr < 127)
        {
            const auto data(charset[chr - 33 + (line * kCharsetCount)]);
            
            mDisplay.writeData(colorMap.data[(data >> 6) & 0x3]);
            mDisplay.writeData(colorMap.data[(data >> 4) & 0x3]);
            mDisplay.writeData(colorMap.data[(data >> 2) & 0x3]);
            mDisplay.writeData(colorMap.data[data & 0x3]);

        }
        else if (chr == 32)
        {
            mDisplay.writeData(colorMap.data[0]);
            mDisplay.writeData(colorMap.data[0]);
            mDisplay.writeData(colorMap.data[0]);
            mDisplay.writeData(colorMap.data[0]);
        }
    }   
}

void Surface::paintTextLineC(const char*     text,
                             const int       width,
                             const int       line,
                             const ColorMap& colorMap)
{
    auto hWidth(width / 2);
    
    int prePad(0);
    int textLen(strlen(text) * 4);

    if (hWidth > textLen)
    {
        prePad = (hWidth - textLen) / 2;
    }

    for (int i(0); i < prePad; ++i)
    {
        mDisplay.writeData(colorMap.data[0]);
    }

    paintTextLine(text, text + strlen(text), line, colorMap);

    for (int i(0); i < (hWidth - (textLen + prePad)); ++i)
    {
        mDisplay.writeData(colorMap.data[0]);
    }
}

void Surface::scroll(uint8_t value)
{
    mDisplay.scroll(value);
}

void Surface::clear()
{
    mDisplay.clear();
    mDisplay.scroll(0);
}

}
