#ifndef INCLUDED_KEYS_H
#define INCLUDED_KEYS_H

#include "data/keycodes.h"
#include "event/event.h"
#include "event/keyevent.h"
#include "event/screenevent.h"

namespace Keys
{

inline
constexpr bool up(const Event& event)
{
    return event == KeyEvent::create(KeyCodes::Up);
}

inline
constexpr bool down(const Event& event)
{
    return event == KeyEvent::create(KeyCodes::Down);
}

inline
constexpr bool pageUp(const Event& event)
{
    return event == KeyEvent::create(KeyCodes::PageUp);
}

inline
constexpr bool pageDown(const Event& event)
{
    return event == KeyEvent::create(KeyCodes::PageDown);
}

inline
constexpr bool left(const Event& event)
{
    return event == KeyEvent::create(KeyCodes::Left);
}

inline
constexpr bool right(const Event& event)
{
    return event == KeyEvent::create(KeyCodes::Right);
}

inline
constexpr bool ok(const Event& event)
{
    return event == KeyEvent::create(KeyCodes::Enter);
}

inline
constexpr bool cancel(const Event& event)
{
    return (event == KeyEvent::create(KeyCodes::Esc) ||
            event == ScreenEvent::create(ScreenId::Type::kHome, 0));
}

inline
constexpr bool backspace(const Event& event)
{
    return event == KeyEvent::create(KeyCodes::Backspace);
}

}

#endif
