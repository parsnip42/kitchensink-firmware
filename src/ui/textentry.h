#ifndef INCLUDED_UI_TEXTENTRY_H
#define INCLUDED_UI_TEXTENTRY_H

#include "types/strbuf.h"
#include "types/strref.h"

#include <cstdint>

class KeyId;
class KeyProcessor;

namespace UI { class Surface; }
namespace UI { class Rectangle; }

namespace UI
{

class TextEntry
{
public:
    TextEntry(Surface&         surface,
              KeyProcessor&    keyProcessor,
              const Rectangle& rect,
              const StrRef&    text);

public:
    bool focus();

    StrRef text() const;

private:
    void paintText();
    void paintCursor(bool visible);
    
private:
    Surface&      mSurface;
    KeyProcessor& mKeyProcessor;
    int           mX;
    int           mY;
    int           mWidth;
    StrBuf<30>    mText;
    std::size_t   mCursorPosition;
    
private:
    TextEntry(const TextEntry&) = delete;
    TextEntry& operator=(const TextEntry&) = delete;
};


inline
StrRef TextEntry::text() const
{
    return mText;
}

}

#endif
