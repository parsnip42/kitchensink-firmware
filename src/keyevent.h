#ifndef INCLUDED_KEYEVENT_H
#define INCLUDED_KEYEVENT_H

#include "keyid.h"

#include <cstdint>

class KeyEvent
{
public:
    KeyEvent();

    explicit KeyEvent(const KeyId& nKeyId,
                      bool         nPressed = true,
                      uint8_t      nTaps = 0);
    
public:
    KeyId   keyId;
    bool    pressed;
    uint8_t taps;
};

inline
KeyEvent::KeyEvent()
    : keyId(KeyId::None)
    , pressed(false)
    , taps(0)
{ }

inline
KeyEvent::KeyEvent(const KeyId& nKeyId,
                   bool         nPressed,
                   uint8_t      nTaps)
    : keyId(nKeyId)
    , pressed(nPressed)
    , taps(nTaps)
{ }

#endif
