#include "ui/textscreen.h"

#include "ui/surface.h"
#include "types/strref.h"

TextScreen::TextScreen(Surface& surface)
    : mSurface(surface)
    , mLines(0)
{ }

void TextScreen::init()
{
    mSurface.clear();
}

void TextScreen::appendLine(const StrRef& text)
{
    const Surface::ColorMap colors(0xf, 0);

    for (int y(0); y < Surface::kFontHeight; ++y)
    {
        mSurface.clearRegion(0, y + (mLines * Surface::kFontHeight), Surface::kWidth, 1, 0x0);
        mSurface.initRegion(0, y + (mLines * Surface::kFontHeight), Surface::kFontWidth * text.length(), 1);
        mSurface.paintTextLine(text, y, colors);
    }

    int scrollStart((mLines * Surface::kFontHeight) - Surface::kHeight);

    ++mLines;

    if (scrollStart > 0)
    {
        int scrollEnd((mLines * Surface::kFontHeight) - Surface::kHeight);
        
        for (int i(scrollStart); i <= scrollEnd; ++i)
        {
            mSurface.scroll(i);
        }
    }
}

