#include "autorepeat.h"

#include "data/keycodes.h"
#include "event/keyevent.h"

AutoRepeat::AutoRepeat(Timer&         timer,
                       EventStage& next)
    : repeatDelay(660)
    , repeatRate(40)
    , mRepeatTimer(timer.createHandle())
    , mNext(next)
{ }

void AutoRepeat::processEvent(const Event& event)
{
    if (mRepeatTimer.matches(event))
    {
        if (mEvent != Event())
        {
            mNext.processEvent(mEvent);
            mNext.processEvent(mEvent.invert());
        }
    }
    else
    {
        if (event.is<KeyEvent>())
        {
            auto keyEvent(event.get<KeyEvent>());
            auto keyCode(keyEvent.keyCode);

            if (keyCode > 0 &&
                keyCode < KeyCodes::ModifierOffset &&
                keyEvent.pressed)
            {
                mEvent = event;
                mRepeatTimer.scheduleRepeating(repeatDelay,
                                               repeatRate);
            }
            else if (!keyEvent.pressed && event.invert() == mEvent)
            {
                mRepeatTimer.cancel();
                mEvent = Event();
            }
        }

        mNext.processEvent(event);
    }
}
