#ifndef INCLUDED_TIMED_H
#define INCLUDED_TIMED_H

#include <cstdint>

// Arduino headers mess with std C++ libs
namespace TimedImpl
{
uint32_t nowMs();
void delayMs(uint32_t ms);
}

template <typename Func>
void Timed(uint32_t timeMs, const Func& func)
{
    auto start(TimedImpl::nowMs());

    func();

    auto processingTime(TimedImpl::nowMs() - start);

    if (processingTime < timeMs)
    {
        TimedImpl::delayMs(timeMs - processingTime);
    }
};

template <typename ActionFunc, typename PollFunc>
void Timed(uint32_t          timeMs,
           const ActionFunc& actionFunc,
           const PollFunc&   pollFunc)
{
    auto start(TimedImpl::nowMs());

    actionFunc();

    while ((TimedImpl::nowMs() - start) < timeMs)
    {
        pollFunc();
    }
};

#endif
