#include "surface.h"
#include "display.h"

#include "types/strref.h"

namespace UI
{

Surface::Surface(Display& display)
    : mDisplay(display)
{ }

void Surface::paintText(int                  x,
                        int                  y,
                        const Types::StrRef& text,
                        uint8_t              fg,
                        uint8_t              bg)
{
    auto len(text.size());
    
    initRegion(x, y, len * kFontWidth, kFontHeight);

    const ColorMap colorMap(fg, bg);
    
    for (int line(0); line < kFontHeight; ++line)
    {
        paintTextLine(text, line, colorMap);
    }
}

void Surface::rectangle(int x, int y, int w, int h)
{
    mDisplay.initRegion(x, y, w, 1);
    
    for (int i = 0; i < (w >> 1); ++i)
    {
        mDisplay.writeData(0xff);
    }

    mDisplay.initRegion(x, y + h, w, 1);
    
    for (int i = 0; i < (w >> 1); ++i)
    {
        mDisplay.writeData(0xff);
    }

    mDisplay.initRegion(x, y + 1, 4, h - 1);
    
    for (int i = 0; i < h - 1; ++i)
    {
        mDisplay.writeData(0xf0);
        mDisplay.writeData(0x0);
    }
    
    mDisplay.initRegion(x + w, y + 1, 4, h - 1);
    
    for (int i = 0; i < h - 1; ++i)
    {
        mDisplay.writeData(0xf0);
        mDisplay.writeData(0x0);
    }
}

void Surface::initRegion(int x, int y, int w, int h)
{
    mDisplay.initRegion(x, y, w, h);
}

void Surface::paintTextLine(const Types::StrRef& text,
                            const int            line,
                            const ColorMap&      colorMap)
{
    for (const auto chr : text)
    {
        uint8_t data(0xff);
        
        if (chr > 32 && chr <= 32 + Font::kCharCount)
        {
            data = Font::fontData[chr - 33 + (line * Font::kCharCount)];
        }
        else if (chr == 32)
        {
            data = 0;
        }

        mDisplay.writeData(colorMap.data[(data >> 6) & 0x3]);
        mDisplay.writeData(colorMap.data[(data >> 4) & 0x3]);
        mDisplay.writeData(colorMap.data[(data >> 2) & 0x3]);
        mDisplay.writeData(colorMap.data[data & 0x3]);
    }   
}

void Surface::paintTextLineC(const Types::StrRef& text,
                             const int            width,
                             const int            line,
                             const ColorMap&      colorMap)
{
    auto hWidth(width / 2);
    
    int prePad(0);
    int textLen(text.size() * 4);

    if (hWidth > textLen)
    {
        prePad = (hWidth - textLen) / 2;
    }

    for (int i(0); i < prePad; ++i)
    {
        mDisplay.writeData(colorMap.data[0]);
    }

    paintTextLine(text, line, colorMap);

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
