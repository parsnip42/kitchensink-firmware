#ifndef INCLUDED_KEYEVENT_H
#define INCLUDED_KEYEVENT_H

#include "data/keycodes.h"
#include "event/event.h"

class KeyEvent
{
public:
    static constexpr Event::Type kType = Event::Type::kKey;

public:
    static constexpr Event create(keycode_t keyCode);

public:
    explicit constexpr KeyEvent(const Event& event);
    
public:
    keycode_t keyCode;
    bool      pressed;

private:
    friend class Event;
};

inline
constexpr Event KeyEvent::create(keycode_t keyCode)
{
    return Event(kType, keyCode);
}

inline
constexpr KeyEvent::KeyEvent(const Event& event)
    : keyCode(event.value())
    , pressed(event.subType() == 0)
{ }

#endif
