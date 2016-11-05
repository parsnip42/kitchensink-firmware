#ifndef INCLUDED_MODIFIER_H
#define INCLUDED_MODIFIER_H

#include "keyevent.h"

#include <cstdint>

class EventQueue;

class Modifier
{
public:
    explicit Modifier(const char*  name  = "",
                      const KeyId& keyId = KeyId::None);

public:
    bool processEvent(const KeyEvent& keyEvent,
                      EventQueue&     eventQueue);

    bool clearTrigger(const KeyEvent& keyEvent,
                      EventQueue&     eventQueue);

    const char* name() const;
    bool active() const;
    bool locked() const;
    
private:
    const char* mName;
    KeyId       mKeyId;
    bool        mLocked;
    bool        mHeld;
    bool        mTrigger;
};


inline
const char* Modifier::name() const
{
    return mName;
}

inline
bool Modifier::active() const
{
    return mLocked || mHeld || mTrigger;
}

inline
bool Modifier::locked() const
{
    return mLocked;
}

#endif
