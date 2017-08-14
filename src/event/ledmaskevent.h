#ifndef INCLUDED_LEDMASKEVENT_H
#define INCLUDED_LEDMASKEVENT_H

#include "event/event.h"

class LedMaskEvent
{
public:
    static constexpr Event::Type kType = Event::Type::kLedMask;

public:
    enum
    {
        NumLock    = 1,
        CapsLock   = 2,
        ScrollLock = 4
    };

public:
    static constexpr Event create(uint8_t mask);
    
private:
    explicit constexpr LedMaskEvent(const Event& event);
    
public:
    uint8_t mask;

private:
    friend class Event;
};


inline
constexpr Event LedMaskEvent::create(uint8_t mask)
{
    return Event(kType, mask);
}

inline
constexpr LedMaskEvent::LedMaskEvent(const Event& event)
    : mask(event.value())
{ }

#endif
