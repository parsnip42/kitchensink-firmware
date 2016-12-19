#include "lock.h"

#include "eventqueue.h"

bool Lock::processEvent(const KeyEvent& keyEvent,
                        uint8_t         taps,
                        EventQueue&     eventQueue)
{
    auto originalState(active());
    
    const auto& keyId(keyEvent.keyId);
    const auto& pressed(keyEvent.pressed);
    
    switch (keyId.lockType())
    {
    case KeyId::LockType::kToggle:
        if (pressed)
        {
            mLocked = !mLocked;
        }
        break;
        
    case KeyId::LockType::kDoubleLock:
        mHeld = pressed;
        mLocked = (taps == 2);
        break;
        
    case KeyId::LockType::kTripleLock:
        mHeld = pressed;
        mLocked = (taps == 3);
        break;

    case KeyId::LockType::kSingle:
        if (pressed)
        {
            mTrigger = !mTrigger;
        }
        break;
        
    case KeyId::LockType::kSingleHold:
        if (pressed)
        {
            mTrigger = !mTrigger;
        }
        mHeld = pressed;
        break;
        
    case KeyId::LockType::kSingleHoldRelease:
        mTrigger = pressed;
        break;
        
    default:
        mHeld = pressed;
        mLocked = false;
        break;

    }

    auto currentState(active());
    
    if (originalState != currentState)
    {
        eventQueue.pushFront(KeyEvent(mKeyId, currentState));

        return true;
    }

    return false;
}

bool Lock::clearTrigger(const KeyEvent& keyEvent,
                        EventQueue&     eventQueue)
{
    if (mTrigger && keyEvent.keyId != mKeyId)
    {
        auto originalState(active());
        
        mTrigger = false;
        
        auto currentState(active());
        
        if (originalState != currentState)
        {
            eventQueue.pushFront(KeyEvent(mKeyId, currentState));

            return true;
        }
    }

    return false;
}
