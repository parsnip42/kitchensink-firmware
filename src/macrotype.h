#ifndef INCLUDED_MACROTYPE_H
#define INCLUDED_MACROTYPE_H

#include <cstdint>

enum class MacroType : uint8_t
{
    kSync   = 0,
    kASync  = 1,
    kInvert = 2
};

#endif
