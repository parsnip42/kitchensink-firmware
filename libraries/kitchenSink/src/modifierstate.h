#ifndef INCLUDED_MODIFIERSTATE_H
#define INCLUDED_MODIFIERSTATE_H

#include "types/bitmask.h"
#include "data/keycode.h"
#include "data/keycodeutil.h"

class Event;

class ModifierState
{
private:
    static constexpr auto kLCtrl  = KeyCodeUtil::modifierIndex(KeyCode::LCtrl);
    static constexpr auto kLShift = KeyCodeUtil::modifierIndex(KeyCode::LShift);
    static constexpr auto kLAlt   = KeyCodeUtil::modifierIndex(KeyCode::LAlt);
    static constexpr auto kLGui   = KeyCodeUtil::modifierIndex(KeyCode::LGui);
    static constexpr auto kRCtrl  = KeyCodeUtil::modifierIndex(KeyCode::RCtrl);
    static constexpr auto kRShift = KeyCodeUtil::modifierIndex(KeyCode::RShift);
    static constexpr auto kRAlt   = KeyCodeUtil::modifierIndex(KeyCode::RAlt);
    static constexpr auto kRGui   = KeyCodeUtil::modifierIndex(KeyCode::RGui);
    
public:
    constexpr ModifierState() = default;

public:
    constexpr bool ctrl() const;
    constexpr bool shift() const;
    constexpr bool alt() const;
    constexpr bool altGr() const;
    constexpr bool gui() const;

    bool processEvent(const Event& event);
    
private:
    Bitmask<KeyCodeUtil::kModifierCount> keyState;
};


inline
constexpr bool ModifierState::ctrl() const
{
    return keyState[kLCtrl] || keyState[kRCtrl];
}

inline
constexpr bool ModifierState::shift() const
{
    return keyState[kLShift] || keyState[kRShift];
}

inline
constexpr bool ModifierState::alt() const
{
    return keyState[kLAlt];
}

inline
constexpr bool ModifierState::altGr() const
{
    return keyState[kRAlt];
}

inline
constexpr bool ModifierState::gui() const
{
    return keyState[kLGui] || keyState[kRGui];
}

#endif
