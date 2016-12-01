#include "text.h"
#include "timed.h"

#include <cstring>

namespace UI
{

Text::Text(Surface& surface)
    : mSurface(surface)
    , mLines(0)
{
    mSurface.clear();
}

void Text::appendLine(const char* text)
{
    const Surface::ColorMap colors(0xf, 0);

    for (int y(0); y < Surface::kFontHeight; ++y)
    {
        mSurface.initRegion(0, y + (mLines * Surface::kFontHeight), Surface::kFontWidth * strlen(text), 1);
        mSurface.paintTextLine(text, text + strlen(text), y, colors);
    }

    int scrollStart((mLines * Surface::kFontHeight) - Surface::kHeight);

    ++mLines;

    if (scrollStart > 0)
    {
        int scrollEnd((mLines * Surface::kFontHeight) - Surface::kHeight);
        
        for (int i(scrollStart); i <= scrollEnd; ++i)
        {
            Timed(4, [&]()
                  {
                      mSurface.scroll(i);
                  });
        }
    }
}


}

