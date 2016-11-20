#include "autorepeat.h"

#include <elapsedMillis.h>

AutoRepeat::AutoRepeat(uint32_t repeatDelay)
    : mRepeatDelay(repeatDelay)
{ }

void AutoRepeat::processEvent(const KeyEvent& keyEvent)
{
    if (keyEvent.pressed)
    {
        mKeyId = keyEvent.keyId;
        mHeldTime = 0;
    }
    else
    {             
        mKeyId = KeyId::None;
    }
}

KeyId AutoRepeat::activeKey()
{
    if (mHeldTime == 0 && mKeyId != KeyId::None)
    {
        mHeldTime = millis();
        return mKeyId;
    }
    
    auto held(millis() - mHeldTime);
    
    if (held > mRepeatDelay)
    {
        return mKeyId;
    }
    else
    {
        return KeyId::None;
    }
}
