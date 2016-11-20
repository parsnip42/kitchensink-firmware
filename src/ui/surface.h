#ifndef INCLUDED_UI_SURFACE_H
#define INCLUDED_UI_SURFACE_H

#include <cstdint>

class Display;

namespace UI
{

class Surface
{
public:
    static constexpr int kHeight = 64;
    static constexpr int kWidth = 240;
    static constexpr int kFontHeight = 14;
    static constexpr uint8_t kScrollMax = 127;

public:
    explicit Surface(Display& display);

public:
    void paintText(int         x,
                   int         y,
                   const char* str,
                   uint8_t     fg = 0xf,
                   uint8_t     bg = 0);

    void initRegion(int x, int y, int w, int h);

    void paintTextLine(const char*   begin,
                       const char*   end,
                       const int     line,
                       const uint8_t (&colorMap)[4]);
    
    void paintTextLineC(const char*   text,
                        const int     width,
                        const int     line,
                        const uint8_t (&colorMap)[4]);

    void scroll(uint8_t value);
    void clear();

private:
    Display& mDisplay;
    
private:
    Surface(const Surface&) = delete;
    Surface& operator=(const Surface&) = delete;
};

}

#endif
