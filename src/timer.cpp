#include "timer.h"

#include "keyevent.h"

void Timer::pollKeyEvent(uint32_t timeMs)
{
    if (!mTimerQueue.empty())
    {
        auto entry(mTimerQueue.peek());
        auto tickId(entry.value.tickId);
        
        if (entry.key <= timeMs)
        {
            mTimerQueue.pop();
            
            if (mTimerActive[tickId])
            {
                auto repeatDelayMs(entry.value.repeatDelayMs);
                
                if (repeatDelayMs > 0)
                {
                    mTimerQueue.insert(TimerQueue::value_type(timeMs + repeatDelayMs,
                                                              Entry(tickId, repeatDelayMs)));
                }
                else
                {
                    mTimerActive[tickId] = false;
                }
                
                mNext.processKeyEvent(KeyEvent(KeyId::Tick(tickId), true));
            }
        }
    }
}

Timer::Handle Timer::schedule(uint32_t timeMs)
{
    return scheduleRepeating(timeMs, 0);
}

Timer::Handle Timer::scheduleRepeating(uint32_t timeMs,
                                       uint32_t repeatDelayMs)
{
    for (std::size_t tickId(0); tickId < mTimerActive.size(); ++tickId)
    {
        auto active(mTimerActive[tickId]);
        
        if (!active)
        {
            active = true;
            
            mTimerQueue.insert(TimerQueue::value_type(timeMs,
                                                      Entry(tickId, repeatDelayMs)));
            
            return Handle(this, tickId);
        }
    }

    return Handle();
}

void Timer::cancel(const Timer::Handle& handle)
{
    mTimerActive[handle.tickId] = false;
}
