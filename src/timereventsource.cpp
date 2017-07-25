#include "timereventsource.h"

#include "keyevent.h"

void TimerEventSource::pollKeyEvent(uint32_t timeMs)
{
    if (!mTimerQueue.empty())
    {
        const auto& entry(mTimerQueue.peek());
        auto tickId(entry.value);
        
        if (entry.key <= timeMs)
        {
            if (mTimerActive[tickId])
            {
                mNext.processKeyEvent(KeyEvent(KeyId::Tick(tickId), true));
                mTimerActive[tickId] = false;
            }
            
            mTimerQueue.pop();
        }
    }
    
    mNextSource.pollKeyEvent(timeMs);
}

TimerEventSource::Handle TimerEventSource::schedule(uint32_t timeMs)
{
    for (std::size_t tickId(0); tickId < mTimerActive.size(); ++tickId)
    {
        auto active(mTimerActive[tickId]);
        
        if (!active)
        {
            active = true;
            
            mTimerQueue.insert(timeMs, tickId);
            
            return Handle(this, tickId);
        }
    }

    return Handle();
}

void TimerEventSource::cancel(const TimerEventSource::Handle& handle)
{
    mTimerActive[handle.tickId] = false;
}
