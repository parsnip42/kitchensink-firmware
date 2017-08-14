#ifndef INCLUDED_TICKEVENT_H
#define INCLUDED_TICKEVENT_H

#include "event/event.h"

class TickEvent
{
public:
    static constexpr Event::Type kType = Event::Type::kTick;

public:
    static constexpr Event create(uint8_t tickId);
    
private:
    explicit constexpr TickEvent(const Event& event);

public:
    uint8_t tickId;

private:
    friend class Event;
};


inline
constexpr Event TickEvent::create(uint8_t tickId)
{
    return Event(kType, tickId);
}

inline
constexpr TickEvent::TickEvent(const Event& event)
    : tickId(event.value())
{ }

#endif
