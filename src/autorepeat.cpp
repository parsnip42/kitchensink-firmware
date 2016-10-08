#include "autorepeat.h"

#include <elapsedMillis.h>

AutoRepeat::AutoRepeat(uint32_t repeatDelay)
    : mRepeatDelay(repeatDelay)
{ }

void AutoRepeat::processKey(const KeyId&    keyId,
                            KeyState::Value state)
{
    if (state == KeyState::kPressed)
    {
        mKeyId = keyId;
        mHeldTime = 0;
    }
    else if (mKeyId == keyId)
    {
        if ((state == KeyState::kHeld) && (mHeldTime == 0))
        {
            mHeldTime = millis();
        }
        else if (state == KeyState::kReleased)
        {             
            mKeyId = KeyId::None;
        }
    }
}

KeyId AutoRepeat::activeKey() const
{
    if ((mHeldTime == 0)
        || (millis() - mHeldTime) > mRepeatDelay)
    {
        return mKeyId;
    }
    else
    {
        return KeyId::None;
    }
}
