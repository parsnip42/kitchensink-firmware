#ifndef INCLUDED_DELAYEVENT_H
#define INCLUDED_DELAYEVENT_H

#include "event/event.h"

class DelayEvent
{
public:
    static constexpr Event::Type kType = Event::Type::kDelay;

public:
    static constexpr Event create(uint32_t delayMs);
    
private:
    explicit constexpr DelayEvent(const Event& event);
    
public:
    uint32_t delayMs;
    
private:
    friend class Event;
};


inline
constexpr Event DelayEvent::create(uint32_t delayMs)
{
    return Event(kType, delayMs >> 8, delayMs);
}

inline
constexpr DelayEvent::DelayEvent(const Event& event)
     : delayMs((event.subType() << 8) | event.value())
{ }

#endif
