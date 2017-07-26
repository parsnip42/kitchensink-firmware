#include "eventmanager.h"

#include <elapsedMillis.h>

Timer::Handle EventManager::schedule(uint32_t delayMs)
{
    return mTimer.schedule(nowMs() + delayMs);
}

Timer::Handle EventManager::scheduleRepeating(uint32_t delayMs)
{
    return mTimer.scheduleRepeating(nowMs() + delayMs, delayMs);
}

void EventManager::cancel(const Timer::Handle& handle)
{
    mTimer.cancel(handle);
}

uint32_t EventManager::nowMs() const
{
    return millis();
}
