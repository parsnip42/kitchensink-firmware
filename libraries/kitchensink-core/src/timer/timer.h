#ifndef INCLUDED_TIMER_H
#define INCLUDED_TIMER_H

#include <cstdint>

class Event;
class TimerManager;

class Timer
{
private:
    Timer(TimerManager* timerManager,
          uint16_t      tickId);

public:
    Timer(Timer&& lhs);
    ~Timer();

public:
    bool matches(const Event& event) const;

    void schedule(uint32_t delayMs);
    
    void scheduleRepeating(uint32_t delayMs,
                           uint32_t repeatDelayMs);

    void cancel();
        
public:
    Timer& operator=(Timer&& lhs);

private:
    TimerManager* mTimerManager;
    uint16_t      mTickId;
        
private:
    Timer(const Timer&) = delete;
    Timer& operator=(const Timer&) = delete;
        
private:
    friend class TimerManager;
};

#endif
