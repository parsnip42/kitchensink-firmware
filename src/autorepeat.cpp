#include "autorepeat.h"

AutoRepeat::AutoRepeat(Timer&         timer,
                       KeyEventStage& next)
    : repeatDelay(660)
    , repeatRate(40)
    , mTimer(timer)
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
        if (event.pressed && keyId.type() == KeyId::Type::kKey)
        {
            mKeyId = keyId;
            mRepeatTimer = mTimer.scheduleRepeating(repeatDelay,
                                                    repeatRate);
        }
        else if (keyId == mKeyId)
        {
            mRepeatTimer.cancel();
            keyId = KeyId();
        }

        mNext.processKeyEvent(event);
    }
}
