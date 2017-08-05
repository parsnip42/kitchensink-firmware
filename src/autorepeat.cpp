#include "autorepeat.h"

#include "data/keycodes.h"

AutoRepeat::AutoRepeat(Timer&         timer,
                       KeyEventStage& next)
    : repeatDelay(660)
    , repeatRate(40)
    , mRepeatTimer(timer.createHandle())
    , mNext(next)
{ }

void AutoRepeat::processKeyEvent(const KeyEvent& event)
{
    auto keyId(event.keyId);
    
    if (mRepeatTimer.matches(event))
    {
        if (mKeyId != KeyId())
        {
            mNext.processKeyEvent(KeyEvent(mKeyId, true));
            mNext.processKeyEvent(KeyEvent(mKeyId, false));
        }
    }
    else
    {
        if (event.pressed &&
            keyId.type() == KeyId::Type::kKey &&
            keyId.value() > 0 &&
            keyId.value() < KeyCodes::ModifierOffset)
        {
            mKeyId = keyId;
            mRepeatTimer.scheduleRepeating(repeatDelay,
                                           repeatRate);
        }
        else if (!event.pressed && keyId == mKeyId)
        {
            mRepeatTimer.cancel();
            keyId = KeyId();
        }

        mNext.processKeyEvent(event);
    }
}
