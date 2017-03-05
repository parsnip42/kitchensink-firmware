#ifndef INCLUDED_UI_KEYS_H
#define INCLUDED_UI_KEYS_H

#include "keycodes.h"
#include "keyid.h"

namespace UI
{
namespace Keys
{

inline
bool up(const KeyId& keyId)
{
    return (keyId == KeyId(KeyCodes::Up) ||
            keyId == KeyId(KeyCodes::E) ||
            keyId == KeyId(KeyCodes::I));
}

inline
bool down(const KeyId& keyId)
{
    return (keyId == KeyId(KeyCodes::Down) ||
            keyId == KeyId(KeyCodes::D) ||
            keyId == KeyId(KeyCodes::K));
}

inline
bool ok(const KeyId& keyId)
{
    return (keyId == KeyId(KeyCodes::Enter) ||
            keyId == KeyId::Action(KeyId::ActionType::kMenu, 0));

}

inline
bool cancel(const KeyId& keyId)
{
    return (keyId == KeyId(KeyCodes::Esc));
}

}
}

#endif
