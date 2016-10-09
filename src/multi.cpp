#include "multi.h"

#include "eventqueue.h"

Multi::Multi()
    : mModifierMask(0)
    , mKeyId(0)
{ }

Multi::Multi(ModifierId modifier,
             int        keyId)
    : mModifierMask(1 << static_cast<int>(modifier))
    , mKeyId(keyId & 0xff)
{ }

void Multi::press(EventQueue& eventQueue)
{
    auto mask(mModifierMask);

    uint8_t modifierId(0);
    
    while (mask)
    {
        if (mask & 1)
        {
            eventQueue.pushBack(KeyEvent(static_cast<ModifierId>(modifierId),
                                         KeyState::kPressed));
        }
        
        mask >>= 1;
        ++modifierId;
    }
    
    if (mKeyId)
    {
        eventQueue.pushBack(KeyEvent(mKeyId, KeyState::kPressed));
    }
}

void Multi::release(EventQueue& eventQueue)
{
    auto mask(mModifierMask);

    uint8_t modifierId(0);
    
    while (mask)
    {
        if (mask & 1)
        {
            eventQueue.pushBack(KeyEvent(static_cast<ModifierId>(modifierId),
                                         KeyState::kReleased));
        }
        
        mask >>= 1;
        ++modifierId;
    }

    if (mKeyId)
    {
        eventQueue.pushBack(KeyEvent(mKeyId, KeyState::kReleased));
    }
}

