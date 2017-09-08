#ifndef INCLUDED_MODIFIERSTATE_H
#define INCLUDED_MODIFIERSTATE_H

#include "types/bitmask.h"
#include "data/keycodes.h"

class Event;

class ModifierState
{
private:
    static constexpr auto kLCtrl  = static_cast<uint8_t>(KeyCode::LCtrl) - KeyCodes::ModifierOffset;
    static constexpr auto kLShift = static_cast<uint8_t>(KeyCode::LShift) - KeyCodes::ModifierOffset;
    static constexpr auto kLAlt   = static_cast<uint8_t>(KeyCode::LAlt) - KeyCodes::ModifierOffset;
    static constexpr auto kLGui   = static_cast<uint8_t>(KeyCode::LGui) - KeyCodes::ModifierOffset;
    static constexpr auto kRCtrl  = static_cast<uint8_t>(KeyCode::RCtrl) - KeyCodes::ModifierOffset;
    static constexpr auto kRShift = static_cast<uint8_t>(KeyCode::RShift) - KeyCodes::ModifierOffset;
    static constexpr auto kRAlt   = static_cast<uint8_t>(KeyCode::RAlt) - KeyCodes::ModifierOffset;
    static constexpr auto kRGui   = static_cast<uint8_t>(KeyCode::RGui) - KeyCodes::ModifierOffset;
    
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
    Bitmask<8> keyState;
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
