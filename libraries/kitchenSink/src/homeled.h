#ifndef INCLUDED_HOMELED_H
#define INCLUDED_HOMELED_H

#include "types/strref.h"
#include "smartkeyset.h"

#include <cstdint>

class StrOutStream;

class HomeLed
{
public:
    enum class Type : uint8_t
    {
        kNone     = 0,
        kKeyboard = 1,
        kSmartKey = 2
    };

    enum KeyboardLed
    {
        kNumLock    = 0,
        kCapsLock   = 1,
        kScrollLock = 2
    };

public:
    HomeLed();
    HomeLed(Type        nType,
            std::size_t nIndex);

public:
    StrRef text(const SmartKeySet& smartKeySet) const;
    
public:
    Type        type;
    std::size_t index;
};


inline
HomeLed::HomeLed()
    : type(Type::kNone)
    , index(0)
{ }

inline
HomeLed::HomeLed(Type        nType,
                 std::size_t nIndex)
    : type(nType)
    , index(nIndex)
{ }

#endif
