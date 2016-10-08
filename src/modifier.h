#ifndef INCLUDED_MODIFIER_H
#define INCLUDED_MODIFIER_H

#include "keystate.h"

#include <cstdint>

class Modifier
{
public:
    Modifier();

public:
    KeyState pressed();
    KeyState released();
    
private:
    uint8_t mRefCount;
};

#endif
