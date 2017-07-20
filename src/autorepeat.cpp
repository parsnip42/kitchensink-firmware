#include "autorepeat.h"

#include <elapsedMillis.h>

AutoRepeat::AutoRepeat(uint32_t repeatDelay,
                       uint32_t repeatRate)
    : mRepeatDelay(repeatDelay)
    , mRepeatRate(repeatRate)
    , mKeyId()
    , mNextTime(0)
{ }

void AutoRepeat::processKeyEvent(const KeyEvent& keyEvent)
{
    if (keyEvent.pressed)
    {
        mKeyId = keyEvent.keyId;
        mNextTime = 0;
    }
    else
    {             
        mKeyId = KeyId();
    }
}

KeyId AutoRepeat::activeKey()
{
    if (mNextTime == 0 && mKeyId != KeyId())
    {
        mNextTime = millis() + mRepeatDelay;
        return mKeyId;
    }

    auto now(millis());
    
    if (mNextTime <= now)
    {
        mNextTime = now + mRepeatRate;
        return mKeyId;
    }
    else
    {
        return KeyId();
    }
}
