#ifndef INCLUDED_KEYEVENT_H
#define INCLUDED_KEYEVENT_H

#include "keyid.h"

class KeyEvent
{
public:
    constexpr KeyEvent();

    explicit constexpr KeyEvent(const KeyId& nKeyId,
                                bool         nPressed = true);
    
public:
    KeyId keyId;
    bool  pressed;
};

inline
constexpr KeyEvent::KeyEvent()
    : keyId()
    , pressed(false)
{ }

inline
constexpr KeyEvent::KeyEvent(const KeyId& nKeyId,
                             bool         nPressed)
    : keyId(nKeyId)
    , pressed(nPressed)
{ }

#endif
