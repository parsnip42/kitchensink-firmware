#ifndef INCLUDED_MODIFIER_H
#define INCLUDED_MODIFIER_H

#include <cstdint>

class Modifier
{
public:
    Modifier();

public:
    bool active() const;
    bool pressed();
    bool released();
    
public:
    uint8_t mRefCount;
};

#endif
