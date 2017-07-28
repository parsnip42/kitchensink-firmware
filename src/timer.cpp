#include "timer.h"
#include "types/range.h"
#include "keyevent.h"

#include <algorithm>
#include <elapsedMillis.h>

Timer::Timer()
    : mHandleIdCounter(0)
{ }

void Timer::pollKeyEvent(KeyEventStage& next)
{
    auto timeMs(millis());
    
    if (!mTimerQueue.empty())
    {
        // The timers are ordered by absolute time ascending in the queue, so
        // the timer at the front will be the next due to fire.
        if (mTimerQueue.peek().key <= timeMs)
        {
            auto tick(mTimerQueue.pop().value);

            next.processKeyEvent(KeyEvent(KeyId::Tick(tick), true));

            auto& timerEntry(mTimerMap[tick]);
            
            if (timerEntry.handleId != 0)
            {
                auto repeatDelayMs(timerEntry.repeatDelayMs);

                // If it's set to repeat, reschedule it and re-insert it into
                // the queue.
                if (repeatDelayMs > 0)
                {
                    auto currentMs(timeMs + repeatDelayMs);
                
                    // Note that we don't change the handleId here - the
                    // corresponding Handle is of course still valid!
                    timerEntry.currentMs = currentMs;
                    mTimerQueue.insert(TimerQueue::value_type(currentMs, tick));
                }
                else
                {
                    timerEntry.clear();
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
    for (uint16_t tick(1); tick < mTimerMap.size(); ++tick)
    {
        auto& timerEntry(mTimerMap[tick]);
        
        if (timerEntry.handleId == 0)
        {
            auto timeMs(delayMs + millis());
            auto handleId(++mHandleIdCounter);
            
            timerEntry.currentMs     = timeMs;
            timerEntry.repeatDelayMs = repeatDelayMs;
            timerEntry.handleId      = handleId;
            
            mTimerQueue.insert(TimerQueue::value_type(timeMs, tick));
            
            return Handle(this, tick, handleId);
        }
    }

    return Handle();
}

bool Timer::active(const Timer::Handle& handle) const
{
    return ((handle.mHandleId != 0) &&
            (mTimerMap[handle.mTick].handleId == handle.mHandleId));
}

void Timer::cancel(const Timer::Handle& handle)
{
    auto& timerEntry(mTimerMap[handle.mTick]);

    // Check that this handle still corresponds to the timer that created it -
    // if it doesn't then this is usually because the life of the Handle object
    // has exceeded that of the timer, and the tick slot has since been reused.
    if (timerEntry.handleId == handle.mHandleId)
    {
        // The timestamp of the timer isn't *absolutely* guaranteed to be
        // unique, but it usually will be - so we can binary search the matching
        // range and then linear search for what is usually going to be a range
        // length of 1.
        
        Range<TimerQueue::iterator> range(
            std::equal_range(mTimerQueue.begin(),
                             mTimerQueue.end(),
                             timerEntry.currentMs));
        
        for (auto it(range.begin()); it != range.end(); ++it)
        {
            // Two identical ticks shouldn't ever be in the queue, let alone in
            // the same place, so we can break out early as soon as we find and
            // erase the target timer.
            if (it->value == handle.mTick)
            {
                mTimerQueue.erase(it);
                break;
            }
        }
        
        timerEntry.clear();
    }
}

std::size_t Timer::activeTimers() const
{
    return mTimerQueue.size();
}












