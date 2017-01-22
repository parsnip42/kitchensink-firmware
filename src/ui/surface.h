#ifndef INCLUDED_UI_SURFACE_H
#define INCLUDED_UI_SURFACE_H

#include "ui/font.h"

#include <cstdint>

class Display;

namespace Types { class StrRef; }

namespace UI
{

class Surface
{
public:
    static constexpr int kHeight = 64;
    static constexpr int kWidth = 240;
    static constexpr int kFontWidth = Font::kWidth;
    static constexpr int kFontHeight = Font::kHeight;
    static constexpr uint8_t kScrollMax = 128;

public:
    class ColorMap
    {
    public:
        constexpr ColorMap(uint8_t fg, uint8_t bg);
        
    public:
        uint8_t data[4];
    };
    
public:
    explicit Surface(Display& display);

public:
    void paintText(int                  x,
                   int                  y,
                   const Types::StrRef& text,
                   uint8_t              fg = 0xf,
                   uint8_t              bg = 0);

    void rectangle(int x, int y, int w, int h);

    void initRegion(int x, int y, int w, int h);

    void paintTextLine(const Types::StrRef& text,
                       const int            line,
                       const ColorMap&      colorMap);
    
    void paintTextLineC(const Types::StrRef& text,
                        const int            width,
                        const int            line,
                        const ColorMap&      colorMap);

    void scroll(uint8_t value);
    void clear();

private:
    Display& mDisplay;
    
private:
    Surface(const Surface&) = delete;
    Surface& operator=(const Surface&) = delete;
};


inline
constexpr Surface::ColorMap::ColorMap(uint8_t fg, uint8_t bg)
    : data {
        uint8_t(bg | (bg << 4)),
        uint8_t(fg | (bg << 4)),
        uint8_t(bg | (fg << 4)),
        uint8_t(fg | (fg << 4))
    }
{ }

}

#endif
