#include "autorepeat.h"

#include "data/keycode.h"
#include "data/keycodeutil.h"
#include "event/keyevent.h"

AutoRepeat::AutoRepeat(Timer&         timer,
                       EventStage& next)
    : repeatDelay(660)
    , repeatRate(40)
    , mRepeatTimer(timer.createHandle())
    , mNext(next)
{ }

bool AutoRepeat::processEvent(const Event& event)
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

            if (!KeyCodeUtil::modifier(keyEvent.key) && keyEvent.pressed)
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

        return mNext.processEvent(event);
    }

    return true;
}
