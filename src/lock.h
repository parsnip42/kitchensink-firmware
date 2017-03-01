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

    Lock(const Types::StrRef& nName,
         const KeyId&         nKeyId);
    
public:
    bool processEvent(const KeyEvent& keyEvent,
                      uint8_t         taps,
                      EventQueue&     eventQueue);

    bool clearTrigger(const KeyEvent& keyEvent,
                      EventQueue&     eventQueue);

    bool active() const;
    bool locked() const;

public:
    Types::StrBuf<12> name;
    KeyId             keyId;
    
private:
    bool  mLocked;
    bool  mHeld;
    bool  mTrigger;
};


inline
constexpr Lock::Lock()
    : name()
    , keyId()
    , mLocked(false)
    , mHeld(false)
    , mTrigger(false)
{ }

inline
Lock::Lock(const Types::StrRef& nName,
           const KeyId&         nKeyId)
    : name(nName)
    , keyId(nKeyId)
    , mLocked(false)
    , mHeld(false)
    , mTrigger(false)
{ }

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
