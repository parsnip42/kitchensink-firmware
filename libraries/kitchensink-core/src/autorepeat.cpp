#include "autorepeat.h"

#include "data/keycode.h"
#include "data/keycodeutil.h"
#include "event/keyevent.h"
#include "globalconfig.h"

AutoRepeat::AutoRepeat(TimerManager& timer,
                       GlobalConfig& globalConfig,
                       EventStage&   next)
    : mRepeatTimer(timer.createTimer())
    , mGlobalConfig(globalConfig)
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
                mRepeatTimer.scheduleRepeating(mGlobalConfig.keyRepeatDelay,
                                               mGlobalConfig.keyRepeatRate);
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
