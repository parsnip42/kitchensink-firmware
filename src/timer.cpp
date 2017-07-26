#include "timer.h"

#include "keyevent.h"

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
            auto tickId(entry.value.tickId);

            auto repeatDelayMs(entry.value.repeatDelayMs);
                
            if (repeatDelayMs > 0)
            {
                mTimerMap[tickId] = mTimerQueue.insert(
                    TimerQueue::value_type(timeMs + repeatDelayMs, entry.value));
            }
            else
            {
                mTimerMap[tickId] = TimerQueue::iterator();
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
        if (mTimerMap[tickId] == TimerQueue::iterator())
        {
            mTimerMap[tickId] = mTimerQueue.insert(
                TimerQueue::value_type(timeMs,
                                       Entry(tickId, repeatDelayMs)));
            
            return Handle(this, tickId);
        }
    }
    
    return Handle();
}

void Timer::cancel(const Timer::Handle& handle)
{
    auto& it(mTimerMap[handle.tickId]);

    if (it != TimerQueue::iterator())
    {
        (*it).value = Entry();
        //mTimerQueue.erase(it);
        mTimerMap[handle.tickId] = TimerQueue::iterator();
    }
}








