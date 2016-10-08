#ifndef INCLUDED_KEYSTATE_H
#define INCLUDED_KEYSTATE_H

#include <cstdint>

enum class KeyState : uint8_t
{
    kNone     = 0,
    kReleased = 1,
    kPressed  = 2,
};

#endif
