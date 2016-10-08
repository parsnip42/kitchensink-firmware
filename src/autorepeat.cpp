#include "autorepeat.h"

#include <elapsedMillis.h>

AutoRepeat::AutoRepeat(uint32_t repeatDelay)
    : mRepeatDelay(repeatDelay)
{ }

void AutoRepeat::processKey(const KeyId& keyId,
                            KeyState     state)
{
    if (state == KeyState::kPressed)
    {
        mKeyId = keyId;
        mHeldTime = millis();
    }
    else if (state == KeyState::kReleased)
    {             
        mKeyId = KeyId::None;
    }
}

KeyId AutoRepeat::activeKey() const
{
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
