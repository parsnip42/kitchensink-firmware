#ifndef INCLUDED_UI_SURFACE_H
#define INCLUDED_UI_SURFACE_H

#include "ui/font.h"
#include "types/ui4array.h"
#include "types/range.h"
#include "types/arrayref.h"
#include <array>
#include <cstdint>

class StrRef;
class Display;

class Surface
{
public:
    static constexpr int     kHeight     = 64;
    static constexpr int     kWidth      = 240;
    static constexpr int     kFontWidth  = Font::kWidth;
    static constexpr int     kFontHeight = Font::kHeight;
    static constexpr uint8_t kScrollMax  = 128;

public:
    typedef UI4Array<kWidth> RowBuf;
    typedef ArrayRef<RowBuf> RowData;
    
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
    void render(const RowBuf& row, int y);

    static void render(const StrRef& text, int x, int line, RowData& row, uint8_t fg = 0xf, uint8_t bg = 0x0);

    template <typename Widget>
    static void render(Widget& widget, RowData& row, int y)
    {
        auto region(widget.getRegion());
        
        if (y >= region.y &&
            y < region.y + region.height)
        {
            widget.render(row, y - region.y);
        }
    }
    
    void paintText(int           x,
                   int           y,
                   const StrRef& text,
                   uint8_t       fg = 0xf,
                   uint8_t       bg = 0);
    
    void paintTextC(int           x,
                    int           y,
                    const int     width,
                    const StrRef& text,
                    uint8_t       fg = 0xf,
                    uint8_t       bg = 0);
    
    void paintTextL(int           x,
                    int           y,
                    int           width,
                    const StrRef& text,
                    uint8_t       fg = 0xf,
                    uint8_t       bg = 0);

    void rectangle(int x, int y, int w, int h, uint8_t color = 0xf);

    void initRegion(int x, int y, int w, int h);
    void clearRegion(int x, int y, int w, int h, uint8_t color);

    void paintTextLine(const StrRef&   text,
                       const int       line,
                       const ColorMap& colorMap);
    
    void paintTextLineC(const StrRef&   text,
                        const int       width,
                        const int       line,
                        const ColorMap& colorMap);
    
    void paintTextLineL(const StrRef&   text,
                        const int       width,
                        const int       line,
                        const ColorMap& colorMap);

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

#endif
