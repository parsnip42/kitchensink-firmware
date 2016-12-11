#ifndef INCLUDED_MODIFIER_H
#define INCLUDED_MODIFIER_H

#include "keyevent.h"
#include "types/strbuf.h"
#include "types/strref.h"

#include <cstdint>

class EventQueue;

class Modifier
{
public:
    constexpr Modifier();

    Modifier(const Types::StrRef& name,
             const KeyId&         keyId);
    
public:
    bool processEvent(const KeyEvent& keyEvent,
                      uint8_t         taps,
                      EventQueue&     eventQueue);

    bool clearTrigger(const KeyEvent& keyEvent,
                      EventQueue&     eventQueue);

    Types::StrRef name() const;
    bool active() const;
    bool locked() const;
    
private:
    Types::StrBuf<12> mName;
    KeyId             mKeyId;
    bool              mLocked:1;
    bool              mHeld:1;
    bool              mTrigger:1;
};


inline
constexpr Modifier::Modifier()
    : mName()
    , mKeyId()
    , mLocked(false)
    , mHeld(false)
    , mTrigger(false)
{ }

inline
Modifier::Modifier(const Types::StrRef& name,
                   const KeyId&         keyId)
    : mName(name)
    , mKeyId(keyId)
    , mLocked(false)
    , mHeld(false)
    , mTrigger(false)
{ }

inline
Types::StrRef Modifier::name() const
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
