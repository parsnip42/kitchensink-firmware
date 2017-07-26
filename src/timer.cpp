#include "timer.h"
#include "types/range.h"
#include "keyevent.h"

#include <algorithm>

Timer::Timer(KeyEventStage& next)
    : mNext(next)
{ }

void Timer::pollKeyEvent(uint32_t timeMs)
{
    if (!mTimerQueue.empty())
    {
        if (mTimerQueue.peek().key <= timeMs)
        {
            auto entry(mTimerQueue.pop());
            auto tickId(entry.value);

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
            
            mNext.processKeyEvent(KeyEvent(KeyId::Tick(tickId), true));
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
    for (uint16_t tickId(1); tickId < mTimerMap.size(); ++tickId)
    {
        auto currentMs(mTimerMap[tickId].currentMs);
        
        if (currentMs == 0)
        {
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
















