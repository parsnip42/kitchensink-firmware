#ifndef INCLUDED_MODIFIERSTATE_H
#define INCLUDED_MODIFIERSTATE_H

#include "types/bitmask.h"
#include "data/keycodes.h"

class KeyEvent;

class ModifierState
{
private:
    static constexpr auto kLCtrl  = KeyCodes::LCtrl - KeyCodes::ModifierOffset;
    static constexpr auto kLShift = KeyCodes::LShift - KeyCodes::ModifierOffset;
    static constexpr auto kLAlt   = KeyCodes::LAlt - KeyCodes::ModifierOffset;
    static constexpr auto kLGui   = KeyCodes::LGui - KeyCodes::ModifierOffset;
    static constexpr auto kRCtrl  = KeyCodes::RCtrl - KeyCodes::ModifierOffset;
    static constexpr auto kRShift = KeyCodes::RShift - KeyCodes::ModifierOffset;
    static constexpr auto kRAlt   = KeyCodes::RAlt - KeyCodes::ModifierOffset;
    static constexpr auto kRGui   = KeyCodes::RGui - KeyCodes::ModifierOffset;
    
public:
    constexpr ModifierState() = default;

public:
    constexpr bool ctrl() const;
    constexpr bool shift() const;
    constexpr bool alt() const;
    constexpr bool altGr() const;
    constexpr bool gui() const;

    bool processEvent(const KeyEvent& event);
    
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
