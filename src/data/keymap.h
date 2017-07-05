#ifndef INCLUDED_KEYMAP_KEYMAP_H
#define INCLUDED_KEYMAP_KEYMAP_H

#include "types/strref.h"

#include <array>
#include <initializer_list>

namespace KeyMap
{

class Entry
{
public:
    explicit constexpr Entry(const char* nName  = "",
                             char        nDflt  = '\0',
                             char        nShift = '\0');

public:
    const char* name;
    const char  dflt;
    const char  shift;
};

inline
constexpr Entry::Entry(const char* nName,
                       char        nDflt,
                       char        nShift)
    : name(nName)
    , dflt(nDflt)
    , shift(nShift)
{ }

const Entry& getEntry(uint8_t n);
const Entry* getEntry(const StrRef& name);

}

#endif
