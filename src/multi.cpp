#include "multi.h"

#include "keyevent.h"
#include "keyeventstage.h"

void Multi::press()
{
    mReleased = false;
    mTriggered = false;
    mActiveKey = key(++mTaps);
}

void Multi::release(KeyEventStage& next)
{
    mReleased = true;
                
    if (mTriggered)
    {
        // Key has been pressed by the trigger, so this event is now
        // responsible for releasing the key.
        next.processKeyEvent(KeyEvent(mActiveKey, false));
        mTaps = 0;
    }
}

bool Multi::trigger(KeyEventStage& next)
{
    if (!mTriggered)
    {
        mTriggered = true;

        next.processKeyEvent(KeyEvent(mActiveKey, true));
        
        // If the key was marked as released before it was pressed by the
        // trigger, then we need to release it immediately too.
        if (mReleased)
        {
            next.processKeyEvent(KeyEvent(mActiveKey, false));
        }

        mTaps = 0;

        return true;
    }

    return false;

}
