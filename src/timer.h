#ifndef INCLUDED_TIMER_H
#define INCLUDED_TIMER_H

#include "keyid.h"
#include "keyevent.h"
#include "keyeventstage.h"
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
                        uint16_t tick,
                        uint32_t handleId);

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

    public:
        Timer*   mTimer;
        uint16_t mTick;
        uint32_t mHandleId;
        
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
        Entry(Entry&&) = default;

    public:
        void clear();
        
    public:
        uint32_t currentMs;
        uint32_t repeatDelayMs;
        uint32_t handleId;

    private:
        Entry(const Entry&) = delete;
        Entry& operator=(const Entry&) = delete;
    };

private:
    typedef OrderedCircularBuffer<uint32_t, uint16_t, Config::kTimerCount> TimerQueue;
    typedef std::array<Entry, Config::kTimerCount>                         TimerMap;
    
public:
    Timer();
    
public:
    void pollKeyEvent(KeyEventStage& next);

    Handle schedule(uint32_t delayMs);
    Handle scheduleRepeating(uint32_t delayMs,
                             uint32_t repeatDelayMs);

    bool active(const Handle& handle) const;
    void cancel(const Handle& handle);

    std::size_t activeTimers() const;

private:
    TimerMap   mTimerMap;
    TimerQueue mTimerQueue;
    uint32_t   mHandleIdCounter;
    
private:
    Timer(const Timer&) = delete;
    Timer& operator=(const Timer&) = delete;
};


inline
Timer::Handle::Handle(Timer*   timer,
                      uint16_t tick,
                      uint32_t handleId)
    : mTimer(timer)
    , mTick(tick)
    , mHandleId(handleId)
{ }

inline
Timer::Handle::Handle(Handle&& rhs)
{
    mTimer    = rhs.mTimer;
    mTick     = rhs.mTick;
    mHandleId = rhs.mHandleId;
    
    // rhs destructor shouldn't cancel timer - set it to null state
    rhs.mTimer    = nullptr;
    rhs.mTick     = 0;
    rhs.mHandleId = 0;
}

inline
Timer::Handle::Handle()
    : mTimer(nullptr)
    , mTick(0)
    , mHandleId(0)
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
    std::swap(mTick, rhs.mTick);
    std::swap(mHandleId, rhs.mHandleId);

    return *this;
}

inline
bool Timer::Handle::matches(KeyEvent event) const
{
    if (mTimer && mTimer->active(*this))
    {
        return event.keyId == KeyId::Tick(mTick);
    }

    return false;
}

inline
void Timer::Handle::cancel()
{
    if (mTimer)
    {
        mTimer->cancel(*this);
    }
    
    mTimer    = nullptr;
    mTick     = 0;
    mHandleId = 0;
}

inline
Timer::Entry::Entry()
    : currentMs(0)
    , repeatDelayMs(0)
    , handleId(0)
{ }

inline
void Timer::Entry::clear()
{
    currentMs     = 0;
    repeatDelayMs = 0;
    handleId      = 0;
}

#endif
