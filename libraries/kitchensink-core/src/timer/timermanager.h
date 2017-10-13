#ifndef INCLUDED_TIMERMANAGER_H
#define INCLUDED_TIMERMANAGER_H

#include "event/event.h"
#include "event/eventsource.h"
#include "event/tickevent.h"
#include "event/eventstage.h"
#include "types/orderedcircularbuffer.h"
#include "timer/timer.h"
#include "config.h"

#include <cstdint>

class TimerManager : public EventSource
{
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
    TimerManager() = default;
    
public:
    virtual void pollEvent(EventStage& next) override;
    
    Timer createTimer();
    
    void releaseTimer(Timer& timer);

    void schedule(const Timer& timer,
                  uint32_t     delayMs);
    
    void scheduleRepeating(const Timer& timer,
                           uint32_t     delayMs,
                           uint32_t     repeatDelayMs);

    void cancel(const Timer& timer);

    std::size_t allocatedTimers() const;

    std::size_t activeTimers() const;

private:
    TimerMap   mTimerMap;
    TimerQueue mTimerQueue;
    
private:
    TimerManager(const TimerManager&) = delete;
    TimerManager& operator=(const TimerManager&) = delete;
};


inline
TimerManager::Entry::Entry()
    : currentMs(0)
    , repeatDelayMs(0)
    , assigned(false)
{ }

#endif
