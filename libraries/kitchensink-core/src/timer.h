#ifndef INCLUDED_TIMER_H
#define INCLUDED_TIMER_H

#include "event/event.h"
#include "event/tickevent.h"
#include "event/eventstage.h"
#include "types/orderedcircularbuffer.h"
#include "config.h"

#include <cstdint>

class Timer
{
public:
    class Handle
    {
    private:
        explicit Handle(Timer*   timer,
                        uint16_t tickId);

    public:
        Handle(Handle&& lhs);
        ~Handle();

    public:
        bool matches(Event event) const;

        void schedule(uint32_t delayMs);
    
        void scheduleRepeating(uint32_t delayMs,
                               uint32_t repeatDelayMs);

        void cancel();
        
    public:
        Handle& operator=(Handle&& lhs);

    public:
        Timer*   mTimer;
        uint16_t mTickId;
        
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
        
    public:
        uint32_t currentMs;
        uint32_t repeatDelayMs;
        bool     assigned;

    private:
        Entry(const Entry&) = delete;
        Entry& operator=(const Entry&) = delete;
    };

private:
    typedef OrderedCircularBuffer<uint32_t, uint16_t, Config::kTimerCount> TimerQueue;
    typedef std::array<Entry, Config::kTimerCount>                         TimerMap;
    
public:
    Timer() = default;
    
public:
    void pollEvent(EventStage& next);

    Handle createHandle();
    
    void releaseHandle(Handle& handle);

    void schedule(const Handle& handle,
                  uint32_t      delayMs);
    
    void scheduleRepeating(const Handle& handle,
                           uint32_t      delayMs,
                           uint32_t      repeatDelayMs);

    void cancel(const Handle& handle);

    std::size_t allocatedTimers() const;

    std::size_t activeTimers() const;

private:
    TimerMap   mTimerMap;
    TimerQueue mTimerQueue;
    
private:
    Timer(const Timer&) = delete;
    Timer& operator=(const Timer&) = delete;
};


inline
Timer::Handle::Handle(Timer*   timer,
                      uint16_t tickId)
    : mTimer(timer)
    , mTickId(tickId)
{ }

inline
Timer::Handle::Handle(Handle&& rhs)
{
    mTimer  = rhs.mTimer;
    mTickId = rhs.mTickId;
    
    // rhs destructor shouldn't release handle - set it to null state
    rhs.mTimer  = nullptr;
    rhs.mTickId = 0;
}

inline
Timer::Handle::~Handle()
{
    if (mTimer)
    {
        mTimer->releaseHandle(*this);
    }
}

inline
Timer::Handle& Timer::Handle::operator=(Handle&& rhs)
{
    std::swap(mTimer, rhs.mTimer);
    std::swap(mTickId, rhs.mTickId);

    return *this;
}

inline
bool Timer::Handle::matches(Event event) const
{
    if (mTimer)
    {
        return event == TickEvent::create(mTickId);
    }

    return false;
}

inline
void Timer::Handle::schedule(uint32_t delayMs)
{
    if (mTimer)
    {
        mTimer->schedule(*this, delayMs);
    }
}

inline
void Timer::Handle::scheduleRepeating(uint32_t delayMs,
                                      uint32_t repeatDelayMs)
{
    if (mTimer)
    {
        mTimer->scheduleRepeating(*this, delayMs, repeatDelayMs);
    }
}

inline
void Timer::Handle::cancel()
{
    if (mTimer)
    {
        mTimer->cancel(*this);
    }
}

inline
Timer::Entry::Entry()
    : currentMs(0)
    , repeatDelayMs(0)
    , assigned(false)
{ }

#endif
