#ifndef INCLUDED_MODIFIER_H
#define INCLUDED_MODIFIER_H

#include "keyevent.h"

#include <cstdint>

class EventQueue;

class Modifier
{
public:
    explicit Modifier(const KeyId& keyId = KeyId::None);

public:
    bool processEvent(const KeyEvent& keyEvent,
                      EventQueue&     eventQueue);
    
private:
    KeyId mKeyId;
    bool  mLocked;
    bool  mHeld;
};

#endif
