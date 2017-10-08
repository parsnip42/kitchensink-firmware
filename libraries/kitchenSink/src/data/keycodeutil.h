#ifndef INCLUDED_KEYCODEUTIL_H
#define INCLUDED_KEYCODEUTIL_H

#include "data/keycode.h"
#include "types/strref.h"

#include <cstdint>

namespace KeyCodeUtil
{

constexpr uint8_t kModifierOffset = 0xe0;
constexpr size_t  kModifierCount  = 8;

StrRef keyName(KeyCode key);
KeyCode keyCode(const StrRef& keyName);

inline
constexpr bool modifier(KeyCode key)
{
    return ((static_cast<std::size_t>(key) >= kModifierOffset) &&
            (static_cast<std::size_t>(key) < (kModifierOffset + kModifierCount)));
}

inline
constexpr size_t modifierIndex(KeyCode key)
{
    return static_cast<std::size_t>(key) - kModifierOffset;
}

}

#endif
