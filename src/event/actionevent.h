#ifndef INCLUDED_ACTIONEVENT_H
#define INCLUDED_ACTIONEVENT_H

#include "event/event.h"

class ActionEvent
{
public:
    static constexpr Event::Type kType = Event::Type::kAction;

public:
    static constexpr Event create(uint8_t actionId);
    
private:
    explicit constexpr ActionEvent(const Event& event);
    
public:
    uint8_t actionId;

private:
    friend class Event;
};


inline
constexpr Event ActionEvent::create(uint8_t actionId)
{
    return Event(kType, actionId);
}

inline
constexpr ActionEvent::ActionEvent(const Event& event)
    : actionId(event.value())
{ }

#endif
