#include "ui/textscreen.h"

#include "ui/surface.h"
#include "types/strref.h"

TextScreen::TextScreen(Surface& surface)
    : mSurface(surface)
{ }

void TextScreen::init()
{
}

void TextScreen::appendLine(const StrRef& text)
{
    if (mContent.full())
    {
        auto last(mContent.end());

        --last;
        
        mContent.erase(last);
    }

    mContent.pushBack(text);
}

