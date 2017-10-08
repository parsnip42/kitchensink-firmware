#ifndef INCLUDED_LEDMASKEVENT_H
#define INCLUDED_LEDMASKEVENT_H

#include "event/event.h"

class LedMaskEvent
{
public:
    static constexpr Event::Type kType = Event::Type::kLedMask;

private:
    enum
    {
        kNumLock    = 1,
        kCapsLock   = 2,
        kScrollLock = 4
    };

public:
    static constexpr Event create(uint8_t mask);
    
private:
    explicit constexpr LedMaskEvent(const Event& event);

public:
    bool numLock() const;
    bool capsLock() const;
    bool scrollLock() const;
    
private:
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

inline
bool LedMaskEvent::numLock() const
{
    return mask & kNumLock;
}

inline
bool LedMaskEvent::capsLock() const
{
    return mask & kCapsLock;
}

inline
bool LedMaskEvent::scrollLock() const
{
    return mask & kScrollLock;
}

#endif
