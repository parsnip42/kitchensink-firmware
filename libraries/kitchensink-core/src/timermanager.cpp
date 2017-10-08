#include "timermanager.h"
#include "types/range.h"
#include "event/event.h"
#include "hardware/ctrlutil.h"

#include <algorithm>

void TimerManager::pollEvent(EventStage& next)
{
    auto timeMs(CtrlUtil::nowMs());
    
    if (!mTimerQueue.empty())
    {
        // The timers are ordered by absolute time ascending in the queue, so
        // the timer at the front will be the next due to fire.
        if (mTimerQueue.peek().key <= timeMs)
        {
            auto tickId(mTimerQueue.pop().value);
            auto& timerEntry(mTimerMap[tickId]);

            auto repeatDelayMs(timerEntry.repeatDelayMs);

            // If it's set to repeat, reschedule it and re-insert it into
            // the queue.
            if (repeatDelayMs > 0)
            {
                auto currentMs(timeMs + repeatDelayMs);
                
                // Note that we don't change the tickId here - the corresponding
                // Timer is of course still valid!
                timerEntry.currentMs = currentMs;
                mTimerQueue.insert(TimerQueue::value_type(currentMs, tickId));
            }
            else
            {
                timerEntry.currentMs     = 0;
                timerEntry.repeatDelayMs = 0;
            }
            
            next.processEvent(TickEvent::create(tickId));
        }
    }
}

Timer TimerManager::createTimer()
{
    for (uint16_t tickId(0); tickId < mTimerMap.size(); ++tickId)
    {
        auto& timerEntry(mTimerMap[tickId]);
        
        if (!timerEntry.assigned)
        {
            timerEntry.currentMs     = 0;
            timerEntry.repeatDelayMs = 0;
            timerEntry.assigned      = true;
            
            return Timer(this, tickId);
        }
    }

    return Timer(nullptr, 0);
}
    
void TimerManager::releaseTimer(Timer& timer)
{
    cancel(timer);

    // Release entry.
    mTimerMap[timer.mTickId].assigned = false;

    timer.mTimerManager = nullptr;
    timer.mTickId = 0;
}

void TimerManager::schedule(const Timer& timer,
                            uint32_t     delayMs)
{
    scheduleRepeating(timer, delayMs, 0);
}

void TimerManager::scheduleRepeating(const Timer& timer,
                                     uint32_t     delayMs,
                                     uint32_t     repeatDelayMs)
{
    cancel(timer);

    auto tickId(timer.mTickId);
    
    auto& timerEntry(mTimerMap[tickId]);

    auto timeMs(delayMs + CtrlUtil::nowMs());
            
    timerEntry.currentMs     = timeMs;
    timerEntry.repeatDelayMs = repeatDelayMs;
            
    mTimerQueue.insert(TimerQueue::value_type(timeMs, tickId));
}

void TimerManager::cancel(const Timer& timer)
{
    auto& timerEntry(mTimerMap[timer.mTickId]);

    if (timerEntry.currentMs != 0)
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
            // Two identical tickIds shouldn't ever be in the queue, let alone in
            // the same place, so we can break out early as soon as we find and
            // erase the target timer.
            if (it->value == timer.mTickId)
            {
                mTimerQueue.erase(it);
                break;
            }
        }
        
    }

    timerEntry.currentMs     = 0;
    timerEntry.repeatDelayMs = 0;
}

std::size_t TimerManager::allocatedTimers() const
{
    std::size_t allocated(0);
    
    for (const auto& timerEntry : mTimerMap)
    {
        if (timerEntry.assigned)
        {
            ++allocated;
        }
    }

    return allocated;
}

std::size_t TimerManager::activeTimers() const
{
    return mTimerQueue.size();
}
