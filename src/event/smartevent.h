#ifndef INCLUDED_SMARTEVENT_H
#define INCLUDED_SMARTEVENT_H

#include "event/event.h"

class SmartEvent
{
public:
    static constexpr Event::Type kType = Event::Type::kSmart;

public:
    static constexpr Event create(uint8_t smartId);
    
private:
    explicit constexpr SmartEvent(const Event& event);
    
public:
    uint8_t smartId;
    bool    pressed;

private:
    friend class Event;
};


inline
constexpr Event SmartEvent::create(uint8_t smartId)
{
    return Event(kType, smartId);
}

inline
constexpr SmartEvent::SmartEvent(const Event& event)
    : smartId(event.value())
    , pressed(!event.subType())
{ }

#endif
