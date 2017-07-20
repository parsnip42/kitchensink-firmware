#ifndef INCLUDED_LOCK_H
#define INCLUDED_LOCK_H

#include "keyevent.h"
#include "types/strbuf.h"
#include "types/strref.h"

#include <cstdint>

class KeyEventStage;

class Lock
{
public:
    constexpr Lock();

    Lock(const StrRef& nName,
         const KeyId&  nKeyId);
    
public:
    bool processEvent(const KeyEvent& keyEvent,
                      uint8_t         taps,
                      KeyEventStage&  next);

    bool clearTrigger(const KeyEvent& keyEvent,
                      KeyEventStage&  next);

    bool active() const;
    bool locked() const;

public:
    StrBuf<12> name;
    KeyId      keyId;
    
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
Lock::Lock(const StrRef& nName,
           const KeyId&  nKeyId)
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
