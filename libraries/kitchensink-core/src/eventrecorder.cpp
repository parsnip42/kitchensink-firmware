#include "eventrecorder.h"

#include "event/delayevent.h"
#include "event/screenevent.h"
#include "event/tickevent.h"
#include "hardware/ctrlutil.h"

EventRecorder::EventRecorder(bool realtime)
    : mLastMs(0)
    , mRealtime(realtime)
    , mContent()
    , mSize(0)
    , mComplete(false)
{ }

bool EventRecorder::processEvent(const Event& event)
{
    if (event != ScreenEvent::create(ScreenEvent::Type::kHome))
    {
        if (event.isUserEvent())
        {
            if (mSize < mContent.size())
            {
                if (mRealtime)
                {
                    auto nowMs(CtrlUtil::nowMs());
                    
                    if (mLastMs != 0)
                    {
                        mContent[mSize++] = DelayEvent::create(nowMs - mLastMs); 
                    }
                    
                    mLastMs = nowMs;
                }
            }
            
            if (mSize < mContent.size())
            {
                mContent[mSize++] = event;
            }
        }
    }
    else
    {
        mComplete = true;
    }

    return true;
}







