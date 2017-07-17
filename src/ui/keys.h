#ifndef INCLUDED_UI_KEYS_H
#define INCLUDED_UI_KEYS_H

#include "data/keycodes.h"
#include "keyid.h"

namespace UI
{
namespace Keys
{

inline
constexpr bool up(const KeyId& keyId)
{
    return keyId == KeyId(KeyCodes::Up);
}

inline
constexpr bool down(const KeyId& keyId)
{
    return keyId == KeyId(KeyCodes::Down);
}

inline
constexpr bool pageUp(const KeyId& keyId)
{
    return keyId == KeyId(KeyCodes::PageUp);
}

inline
constexpr bool pageDown(const KeyId& keyId)
{
    return keyId == KeyId(KeyCodes::PageDown);
}

inline
constexpr bool left(const KeyId& keyId)
{
    return keyId == KeyId(KeyCodes::Left);
}

inline
constexpr bool right(const KeyId& keyId)
{
    return keyId == KeyId(KeyCodes::Right);
}

inline
constexpr bool ok(const KeyId& keyId)
{
    return keyId == KeyId(KeyCodes::Enter);

}

inline
constexpr bool cancel(const KeyId& keyId)
{
    return (keyId == KeyId(KeyCodes::Esc) ||
            keyId == KeyId::Action(KeyId::ActionType::kMenu, 0));
}

}
}

#endif
