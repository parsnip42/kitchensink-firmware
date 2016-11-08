#include "modifier.h"

#include "eventqueue.h"

Modifier::Modifier(const char*  name,
                   const KeyId& keyId)
    : mName(name)
    , mKeyId(keyId)
    , mLocked(false)
    , mHeld(false)
    , mTrigger(false)
{ }

bool Modifier::processEvent(const KeyEvent& keyEvent,
                            uint8_t         taps,
                            EventQueue&     eventQueue)
{
    auto originalState(active());
    
    const auto& keyId(keyEvent.keyId);
    const auto& pressed(keyEvent.pressed);
    
    switch (keyId.modifierType())
    {
    case KeyId::ModifierType::kToggle:
        if (pressed)
        {
            mLocked = !mLocked;
        }
        break;
        
    case KeyId::ModifierType::kDoubleLock:
        mHeld = pressed;
        mLocked = (taps == 2);
        break;
        
    case KeyId::ModifierType::kTripleLock:
        mHeld = pressed;
        mLocked = (taps == 3);
        break;

    case KeyId::ModifierType::kSingle:
        if (pressed)
        {
            mTrigger = !mTrigger;
        }
        break;
        
    case KeyId::ModifierType::kSingleHold:
        if (pressed)
        {
            mTrigger = !mTrigger;
        }
        mHeld = pressed;
        break;
        
    case KeyId::ModifierType::kSingleHoldRelease:
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

bool Modifier::clearTrigger(const KeyEvent& keyEvent,
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
