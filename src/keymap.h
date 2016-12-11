#ifndef INCLUDED_KEYMAP_H
#define INCLUDED_KEYMAP_H

#include "types/strref.h"

#include <array>
#include <initializer_list>

namespace KeyMap
{

class Entry
{
public:
    constexpr Entry();
    
    constexpr Entry(const Types::StrRef& nDflt,
                    const Types::StrRef& nShift);

public:
    const Types::StrRef dflt;
    const Types::StrRef shift;
};

inline
constexpr Entry::Entry()
    : dflt("?")
    , shift("?")
{ }

inline
constexpr Entry::Entry(const Types::StrRef& nDflt,
                       const Types::StrRef& nShift)
    : dflt(nDflt)
    , shift(nShift)
{ }

const Entry& getEntry(uint8_t n);

}

#endif
