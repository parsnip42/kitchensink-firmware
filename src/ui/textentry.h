#ifndef INCLUDED_UI_TEXTENTRY_H
#define INCLUDED_UI_TEXTENTRY_H

#include "types/strref.h"

class KeyProcessor;

namespace UI { class Surface; }

namespace UI
{

class TextEntry
{
public:
    constexpr TextEntry(Surface&             surface,
                        KeyProcessor&        keyProcessor,
                        const Types::StrRef& title);

public:
    void create();
    
private:
    Surface&      mSurface;
    KeyProcessor& mKeyProcessor;
    Types::StrRef mTitle;

private:
    TextEntry(const TextEntry&) = delete;
    TextEntry& operator=(const TextEntry&) = delete;
};


inline
constexpr TextEntry::TextEntry(Surface&             surface,
                               KeyProcessor&        keyProcessor,
                               const Types::StrRef& title)
    : mSurface(surface)
    , mKeyProcessor(keyProcessor)
    , mTitle(title)
{ }

}

#endif
