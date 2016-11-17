#include "ui/menu.h"

#include <cmath>
#include <cstdint>

namespace UI
{

Menu::Menu(Surface& surface)
    : mSurface(surface)
{ }

void Menu::paint()
{
    int point(0);
    uint8_t fg(0xf);
    uint8_t bg(0);
    int len(3);
    
    mSurface.initRegion(28, 0, len << 3, 64);

    const uint8_t colorMap[] =
    {
        uint8_t(bg | (bg << 4)),
        uint8_t(bg | (fg << 4)),
        uint8_t(fg | (bg << 4)),
        uint8_t(fg | (fg << 4)),
    };

    const uint8_t invColorMap[] =
    {
        uint8_t(fg | (fg << 4)),
        uint8_t(fg | (bg << 4)),
        uint8_t(bg | (fg << 4)),
        uint8_t(bg | (bg << 4)),
    };
    
    for (auto offset(point); offset < point + 64; ++offset)
    {
        auto index((point + offset) / 14);
        auto line((point + offset) % 14);

        const char* text("TEST");
        
        // if ((index % dataSource.size()) == (selected % dataSource.size()))
        // {
        //     mSurface.paintTextLine(text, text+len, line, invColorMap);
        // }
        // else
        {
            mSurface.paintTextLine(text, text+len, line, colorMap);
        }
    }
}

}
