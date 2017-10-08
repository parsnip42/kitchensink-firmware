#include "multikey.h"

#include "event/eventstage.h"

void MultiKey::press()
{
    mReleased = false;
    mTriggered = false;
    mActiveEvent = event(++mTaps);
}

void MultiKey::release(EventStage& next)
{
    mReleased = true;
                
    if (mTriggered)
    {
        // Key has been pressed by the trigger, so this event is now
        // responsible for releasing the key.
        mTaps = 0;
        next.processEvent(mActiveEvent.invert());
    }
}

bool MultiKey::trigger(EventStage& next)
{
    if (!mTriggered)
    {
        mTriggered = true;
        mTaps = 0;

        auto activeEvent(mActiveEvent);
        auto released(mReleased);
        
        next.processEvent(activeEvent);
        
        // If the key was marked as released before it was pressed by the
        // trigger, then we need to release it immediately too.
        if (released)
        {
            next.processEvent(mActiveEvent.invert());
        }

        return true;
    }

    return false;

}
