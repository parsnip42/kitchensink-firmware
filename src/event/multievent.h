#ifndef INCLUDED_MULTIEVENT_H
#define INCLUDED_MULTIEVENT_H

#include "event/event.h"

class MultiEvent
{
public:
    static constexpr Event::Type kType = Event::Type::kMulti;

public:
    static constexpr Event create(uint8_t multiId);
    
private:
    explicit constexpr MultiEvent(const Event& event);
    
public:
    uint8_t multiId;
    bool    pressed;

private:
    friend class Event;
};


inline
constexpr Event MultiEvent::create(uint8_t multiId)
{
    return Event(kType, multiId);
}

inline
constexpr MultiEvent::MultiEvent(const Event& event)
    : multiId(event.value())
    , pressed(!event.inverted())
{ }

#endif
