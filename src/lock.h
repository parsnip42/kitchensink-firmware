#ifndef INCLUDED_LOCK_H
#define INCLUDED_LOCK_H

#include "keyevent.h"
#include "types/strbuf.h"
#include "types/strref.h"

#include <cstdint>

class EventQueue;

class Lock
{
public:
    constexpr Lock();

    Lock(const Types::StrRef& name,
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
    bool              mLocked;
    bool              mHeld;
    bool              mTrigger;
};


inline
constexpr Lock::Lock()
    : mName()
    , mKeyId()
    , mLocked(false)
    , mHeld(false)
    , mTrigger(false)
{ }

inline
Lock::Lock(const Types::StrRef& name,
           const KeyId&         keyId)
    : mName(name)
    , mKeyId(keyId)
    , mLocked(false)
    , mHeld(false)
    , mTrigger(false)
{ }

inline
Types::StrRef Lock::name() const
{
    return mName;
}

inline
bool Lock::active() const
{
    return mLocked || mHeld || mTrigger;
}

inline
bool Lock::locked() const
{
    return mLocked;
}

#endif
