#ifndef INCLUDED_KEYEVENT_H
#define INCLUDED_KEYEVENT_H

#include "keyid.h"
#include "keystate.h"

#include <cstdint>

class KeyEvent
{
public:
    KeyEvent();

    KeyEvent(const KeyId& nKeyId,
             KeyState     nState,
             uint8_t      nTaps = 0);
    
public:
    KeyId    keyId;
    KeyState state;
    uint8_t  taps;
};

inline
KeyEvent::KeyEvent()
    : keyId(KeyId::None)
    , state(KeyState::kNone)
    , taps(0)
{ }

inline
KeyEvent::KeyEvent(const KeyId& nKeyId,
                   KeyState     nState,
                   uint8_t      nTaps)
    : keyId(nKeyId)
    , state(nState)
    , taps(nTaps)
{ }

#endif
