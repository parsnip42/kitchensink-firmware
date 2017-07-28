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
        mTaps = 0;
        next.processKeyEvent(KeyEvent(mActiveKey, false));
    }
}

bool Multi::trigger(KeyEventStage& next)
{
    if (!mTriggered)
    {
        mTriggered = true;
        mTaps = 0;

        auto activeKey(mActiveKey);
        auto released(mReleased);
        
        next.processKeyEvent(KeyEvent(activeKey, true));
        
        // If the key was marked as released before it was pressed by the
        // trigger, then we need to release it immediately too.
        if (released)
        {
            next.processKeyEvent(KeyEvent(activeKey, false));
        }

        return true;
    }

    return false;

}
