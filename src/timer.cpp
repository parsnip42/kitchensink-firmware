#include "timer.h"
#include "types/range.h"
#include "keyevent.h"

#include <algorithm>
#include <elapsedMillis.h>

Timer::Timer()
{ }

void Timer::pollKeyEvent(uint32_t       timeMs,
                         KeyEventStage& next)
{
    if (!mTimerQueue.empty())
    {
        if (mTimerQueue.peek().key <= timeMs)
        {
            auto entry(mTimerQueue.pop());
            auto tickId(entry.value);

            next.processKeyEvent(KeyEvent(KeyId::Tick(tickId), true));

            if (mTimerMap[tickId].currentMs != 0)
            {
                auto repeatDelayMs(mTimerMap[tickId].repeatDelayMs);
                
                if (repeatDelayMs > 0)
                {
                    auto currentMs(timeMs + repeatDelayMs);
                    
                    mTimerMap[tickId].currentMs = currentMs;
                    mTimerQueue.insert(TimerQueue::value_type(currentMs, tickId));
                }
                else
                {
                    mTimerMap[tickId].currentMs = 0;
                }
            }
            
        }
    }
}

Timer::Handle Timer::schedule(uint32_t delayMs)
{
    return scheduleRepeating(delayMs, 0);
}

Timer::Handle Timer::scheduleRepeating(uint32_t delayMs,
                                       uint32_t repeatDelayMs)
{
    for (uint16_t tickId(1); tickId < mTimerMap.size(); ++tickId)
    {
        auto currentMs(mTimerMap[tickId].currentMs);
        
        if (currentMs == 0)
        {
            auto timeMs(delayMs + millis());

            mTimerMap[tickId].currentMs = timeMs;
            mTimerMap[tickId].repeatDelayMs = repeatDelayMs;
            
            mTimerQueue.insert(
                TimerQueue::value_type(timeMs, tickId));
            
            return Handle(this, tickId);
        }
    }

    return Handle();
}

void Timer::cancel(const Timer::Handle& handle)
{
    Range<TimerQueue::iterator> range(
        std::equal_range(mTimerQueue.begin(),
                         mTimerQueue.end(),
                         mTimerMap[handle.tickId].currentMs));

    for (auto it(range.begin()); it != range.end(); ++it)
    {
        if ((*it).value == handle.tickId)
        {
            mTimerQueue.erase(it);
            break;
        }
    }
    
    mTimerMap[handle.tickId].currentMs = 0;
}
















