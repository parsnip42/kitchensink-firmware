#ifndef INCLUDED_KEYMAP_H
#define INCLUDED_KEYMAP_H

#include <array>
#include <initializer_list>

namespace KeyMap
{

class Entry
{
public:
    Entry();
    
    Entry(const char* nDflt,
          const char* nShift);

public:
    const char* dflt;
    const char* shift;
};

const std::array<Entry, 0xff>& table();

}

#endif
