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
    
    constexpr Entry(char nDflt,
                    char nShift);

public:
    const char dflt;
    const char shift;
};

inline
constexpr Entry::Entry()
    : dflt('?')
    , shift('?')
{ }

inline
constexpr Entry::Entry(char nDflt,
                       char nShift)
    : dflt(nDflt)
    , shift(nShift)
{ }

const Entry& getEntry(uint8_t n);

}

#endif
