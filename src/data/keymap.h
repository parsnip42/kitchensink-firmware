#ifndef INCLUDED_KEYMAP_KEYMAP_H
#define INCLUDED_KEYMAP_KEYMAP_H

#include <cstdint>

namespace KeyMap
{

class Entry
{
public:
    constexpr Entry(char nDflt  = '\0',
                    char nShift = '\0');

public:
    char dflt;
    char shift;
};

inline
constexpr Entry::Entry(char nDflt,
                       char nShift)
    : dflt(nDflt)
    , shift(nShift)
{ }

const Entry& getEntry(uint8_t n);

}

#endif
