#include "modifier.h"

Modifier::Modifier()
    : mRefCount(0)
{ }

KeyState Modifier::pressed()
{
    mRefCount = 1;
    
    return KeyState::kPressed;
}

KeyState Modifier::released()
{
    mRefCount = 1;
        
    return KeyState::kReleased;
}
