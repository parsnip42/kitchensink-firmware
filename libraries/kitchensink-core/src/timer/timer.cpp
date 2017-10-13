#include "timer.h"

#include "timermanager.h"

// Technically there's a cyclic dependency between TimerManager and Timer here,
// but given that they're both part of the same system and fundamentally
// inseparable, that should be fine.

Timer::Timer(TimerManager* timerManager,
             uint16_t      tickId)
    : mTimerManager(timerManager)
    , mTickId(tickId)
{ }

Timer::Timer(Timer&& rhs)
{
    mTimerManager = rhs.mTimerManager;
    mTickId = rhs.mTickId;
    
    // rhs destructor shouldn't release handle - set it to null state
    rhs.mTimerManager = nullptr;
    rhs.mTickId = 0;
}

Timer::~Timer()
{
    if (mTimerManager)
    {
        mTimerManager->releaseTimer(*this);
    }
}

Timer& Timer::operator=(Timer&& rhs)
{
    std::swap(mTimerManager, rhs.mTimerManager);
    std::swap(mTickId, rhs.mTickId);

    return *this;
}

bool Timer::matches(const Event& event) const
{
    if (mTimerManager)
    {
        return event == TickEvent::create(mTickId);
    }

    return false;
}

void Timer::schedule(uint32_t delayMs)
{
    if (mTimerManager)
    {
        mTimerManager->schedule(*this, delayMs);
    }
}

void Timer::scheduleRepeating(uint32_t delayMs,
                              uint32_t repeatDelayMs)
{
    if (mTimerManager)
    {
        mTimerManager->scheduleRepeating(*this, delayMs, repeatDelayMs);
    }
}

void Timer::cancel()
{
    if (mTimerManager)
    {
        mTimerManager->cancel(*this);
    }
}
