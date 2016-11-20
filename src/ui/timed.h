#ifndef INCLUDED_TIMED_H
#define INCLUDED_TIMED_H

#include <elapsedMillis.h>

template <typename Func>
void Timed(uint32_t timeMs, const Func& func)
{
    auto start(millis());

    func();

    auto processingTime(millis() - start);

    if (processingTime < timeMs)
    {
        delay(timeMs - processingTime);
    }
};

template <typename ActionFunc, typename PollFunc>
void Timed(uint32_t          timeMs,
           const ActionFunc& actionFunc,
           const PollFunc&   pollFunc)
{
    auto start(millis());

    actionFunc();

    while ((millis() - start) < timeMs)
    {
        pollFunc();
    }
};

#endif
