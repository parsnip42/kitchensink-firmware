#ifndef INCLUDED_KEYSTATE_H
#define INCLUDED_KEYSTATE_H

namespace KeyState
{

enum Value
{
    kNone     = 0,
    kReleased = 1,
    kHeld     = 2,
    kPressed  = 3
};

inline
Value fromMatrix(bool state, bool delta)
{
    return static_cast<KeyState::Value>((((int)state) << 1) | ((int)delta));
}

};

#endif
