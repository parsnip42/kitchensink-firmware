#ifndef INCLUDED_MULTI_H
#define INCLUDED_MULTI_H

#include "modifierid.h"

#include <cstdint>

class EventQueue;

class Multi
{
public:
    Multi();

    Multi(ModifierId modifier,
          int        keyId);
    
public:
    void press(EventQueue& eventQueue);
    void release(EventQueue& eventQueue);
    
private:
    uint8_t mModifierMask;
    uint8_t mKeyId;
};

#endif
