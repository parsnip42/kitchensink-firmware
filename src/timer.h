#ifndef INCLUDED_TIMER_H
#define INCLUDED_TIMER_H

#include "keyid.h"
#include "keyevent.h"
#include "keyeventstage.h"
#include "keyeventsource.h"
#include "types/orderedcircularbuffer.h"

#include <cstdint>

class Timer : public KeyEventSource
{
public:
    class Handle
    {
    private:
        explicit Handle(Timer*   timer,
                        uint32_t nTickId);

    public:
        Handle();
        Handle(Handle&& lhs);
        ~Handle();

    public:
        bool matches(KeyEvent event) const;
        void cancel();
        
    public:
        Handle& operator=(Handle&& lhs);

    private:
        Timer* mTimer;

    public:
        uint16_t tickId;

    private:
        Handle(const Handle&) = delete;
        Handle& operator=(const Handle&) = delete;
        
    private:
        friend class Timer;
    };

private:
    class Entry
    {
    public:
        Entry();
        Entry(uint32_t currentMs,
              uint32_t nRepeatDelayMs);

    public:
        uint32_t currentMs;
        uint32_t repeatDelayMs;
    };

private:
    typedef OrderedCircularBuffer<uint32_t, uint16_t, 200> TimerQueue;
    typedef std::array<Entry, 200>                         TimerMap;
    
public:
    Timer();
    
public:
    virtual void pollKeyEvent(uint32_t       timeMs,
                              KeyEventStage& next) override;

    Handle schedule(uint32_t delayMs);
    Handle scheduleRepeating(uint32_t delayMs,
                             uint32_t repeatDelayMs);

    void cancel(const Handle& handle);
    
private:
    TimerMap   mTimerMap;
    TimerQueue mTimerQueue;

private:
    Timer(const Timer&) = delete;
    Timer& operator=(const Timer&) = delete;
};


inline
Timer::Handle::Handle(Timer*   timer,
                      uint32_t nTickId)
    : mTimer(timer)
    , tickId(nTickId)
{ }

inline
Timer::Handle::Handle(Handle&& rhs)
{
    mTimer = rhs.mTimer;
    tickId = rhs.tickId;

    // lhs destructor shouldn't cancel timer - set it to null state
    rhs.mTimer = nullptr;
    rhs.tickId = 0;
}

inline
Timer::Handle::Handle()
    : mTimer(nullptr)
    , tickId(0)
{ }

inline
Timer::Handle::~Handle()
{
    cancel();
}

inline
Timer::Handle& Timer::Handle::operator=(Handle&& rhs)
{
    std::swap(mTimer, rhs.mTimer);
    std::swap(tickId, rhs.tickId);

    return *this;
}

inline
bool Timer::Handle::matches(KeyEvent event) const
{
    return event.keyId == KeyId::Tick(tickId);
}

inline
void Timer::Handle::cancel()
{
    if (mTimer)
    {
        mTimer->cancel(*this);
    }
    
    mTimer = nullptr;
    tickId = 0;
}

inline
Timer::Entry::Entry()
    : currentMs(0)
    , repeatDelayMs(0)
{ }

inline
Timer::Entry::Entry(uint32_t nCurrentMs,
                    uint32_t nRepeatDelayMs)
    : currentMs(nCurrentMs)
    , repeatDelayMs(nRepeatDelayMs)
{ }

#endif
