#ifndef INCLUDED_KEYEVENT_H
#define INCLUDED_KEYEVENT_H

#include "data/keycodes.h"
#include "event/event.h"

class KeyEvent
{
public:
    static constexpr Event::Type kType = Event::Type::kKey;

public:
    static constexpr Event create(KeyCode key);

public:
    explicit constexpr KeyEvent(const Event& event);
    
public:
    KeyCode key;
    bool    pressed;

private:
    friend class Event;
};

inline
constexpr Event KeyEvent::create(KeyCode key)
{
    return Event(kType, static_cast<uint8_t>(key));
}

inline
constexpr KeyEvent::KeyEvent(const Event& event)
    : key(static_cast<KeyCode>(event.value()))
    , pressed(event.subType() == 0)
{ }

#endif
