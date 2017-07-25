#ifndef INCLUDED_TIMEREVENTSOURCE_H
#define INCLUDED_TIMEREVENTSOURCE_H

#include "keyid.h"
#include "keyeventstage.h"
#include "keyeventsource.h"
#include "types/bitmask.h"
#include "types/orderedcircularbuffer.h"

#include <cstdint>

class TimerEventSource : public KeyEventSource
{
public:
    class Handle
    {
    private:
        explicit Handle(TimerEventSource* timerEventSource,
                        uint32_t          nTickId)
            : mTimerEventSource(timerEventSource)
            , tickId(nTickId)
        { }

    public:
        Handle()
            : mTimerEventSource(nullptr)
            , tickId(0)
        { }

        Handle(Handle&&) = default;
        
        ~Handle()
        {
            if (mTimerEventSource)
            {
                mTimerEventSource->cancel(*this);
            }
        }

    private:
        TimerEventSource* mTimerEventSource;

    public:
        uint32_t tickId;

    private:
        Handle(const Handle&) = delete;
        Handle& operator=(const Handle&) = delete;
        
    private:
        friend class TimerEventSource;
    };
    
public:
    TimerEventSource(KeyEventSource& nextSource,
                     KeyEventStage&  next);
    
public:
    virtual void pollKeyEvent(uint32_t timeMs);

    Handle schedule(uint32_t delayMs);
    void cancel(const Handle& handle);
        
private:
    Bitmask<20>                              mTimerActive;
    OrderedCircularBuffer<uint32_t, int, 20> mTimerQueue;
    KeyEventSource&                          mNextSource;
    KeyEventStage&                           mNext;
};


inline
TimerEventSource::TimerEventSource(KeyEventSource& nextSource,
                                   KeyEventStage&  next)
    : mNextSource(nextSource)
    , mNext(next)
{ }

#endif /* INCLUDED_TIMEREVENTSOURCE_H */












