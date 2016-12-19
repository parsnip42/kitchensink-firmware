#ifndef INCLUDED_UI_TEXTENTRY_H
#define INCLUDED_UI_TEXTENTRY_H

#include "types/strbuf.h"
#include "types/strref.h"

class KeyProcessor;

namespace UI { class Surface; }

namespace UI
{

class TextEntry
{
public:
    constexpr TextEntry(Surface&      surface,
                        KeyProcessor& keyProcessor);

public:
    bool create(const Types::StrRef& title,
                const Types::StrRef& text = "");

    constexpr Types::StrRef text() const;

private:
    Surface&          mSurface;
    KeyProcessor&     mKeyProcessor;
    Types::StrBuf<30> mText;

private:
    TextEntry(const TextEntry&) = delete;
    TextEntry& operator=(const TextEntry&) = delete;
};


inline
constexpr TextEntry::TextEntry(Surface&      surface,
                               KeyProcessor& keyProcessor)
    : mSurface(surface)
    , mKeyProcessor(keyProcessor)
{ }

inline
constexpr Types::StrRef TextEntry::text() const
{
    return mText;
}


}

#endif
