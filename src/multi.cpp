#include "multi.h"

#include "eventqueue.h"

void Multi::press()
{
    mReleased = false;
    mTriggered = false;
    mActiveKey = key(++mTaps);
}

void Multi::release(EventQueue& eventQueue)
{
    mReleased = true;
                
    if (mTriggered)
    {
        // Key has been pressed by the trigger, so this event is now
        // responsible for releasing the key.
        eventQueue.pushFront(KeyEvent(mActiveKey, false));
        mTaps = 0;
    }
}

bool Multi::trigger(EventQueue& eventQueue)
{
    if (!mTriggered)
    {
        mTriggered = true;

        // If the key was marked as released before it was pressed by the
        // trigger, then we need to release it immediately too.
        if (mReleased)
        {
            eventQueue.pushFront(KeyEvent(mActiveKey, false));
        }
        
        eventQueue.pushFront(KeyEvent(mActiveKey, true));

        mTaps = 0;

        return true;
    }

    return false;

}

bool Multi::trigger(const KeyEvent& triggerEvent,
                    EventQueue&     eventQueue)
{
    if (!mTriggered)
    {
        eventQueue.pushFront(triggerEvent);
    }

    return trigger(eventQueue);
}
