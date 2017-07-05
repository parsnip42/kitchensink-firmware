#ifndef INCLUDED_UI_TEXTENTRY_H
#define INCLUDED_UI_TEXTENTRY_H

#include "types/strbuf.h"
#include "types/strref.h"

#include <cstdint>

class KeyId;
class KeyProcessor;

namespace UI { class Surface; }

namespace UI
{

class TextEntry
{
public:
    TextEntry(Surface&      surface,
              KeyProcessor& keyProcessor,
              int           x,
              int           y,
              int           width,
              const StrRef& text);

public:
    bool create();

    StrRef text() const;

private:
    void processKey(const KeyId& keyId);
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
