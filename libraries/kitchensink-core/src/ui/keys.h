#ifndef INCLUDED_KEYS_H
#define INCLUDED_KEYS_H

#include "data/keycode.h"
#include "event/event.h"
#include "event/keyevent.h"
#include "event/screenevent.h"

namespace Keys
{

inline
constexpr bool prev(const Event& event)
{
    return event == KeyEvent::create(KeyCode::Up);
}

inline
constexpr bool next(const Event& event)
{
    return (event == KeyEvent::create(KeyCode::Down) ||
            event == KeyEvent::create(KeyCode::Tab));
}

inline
constexpr bool pageUp(const Event& event)
{
    return event == KeyEvent::create(KeyCode::PageUp);
}

inline
constexpr bool pageDown(const Event& event)
{
    return event == KeyEvent::create(KeyCode::PageDown);
}

inline
constexpr bool left(const Event& event)
{
    return event == KeyEvent::create(KeyCode::Left);
}

inline
constexpr bool right(const Event& event)
{
    return event == KeyEvent::create(KeyCode::Right);
}

inline
constexpr bool ok(const Event& event)
{
    // HACK: We're waiting for key release here seeing as time consuming events
    // can trigger autorepeat and generally mess things up a bit.
    return event == KeyEvent::create(KeyCode::Enter);
}

inline
constexpr bool okReleased(const Event& event)
{
    return ok(event.invert());
}

inline
constexpr bool cancel(const Event& event)
{
    return (event == KeyEvent::create(KeyCode::Esc) ||
            event == ScreenEvent::create(ScreenEvent::Type::kHome, 0));
}

inline
constexpr bool backspace(const Event& event)
{
    return event == KeyEvent::create(KeyCode::Backspace);
}

}

#endif
