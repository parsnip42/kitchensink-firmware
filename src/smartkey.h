#ifndef INCLUDED_SMARTKEY_H
#define INCLUDED_SMARTKEY_H

#include "keyid.h"

class SmartKey
{
public:
    enum Type : uint8_t
    {
        kToggle            = 0,
        kToggleAutoRelease = 1,
        kHoldAutoRelease   = 2,
        kPair              = 3,
        kHoldOrTap         = 4
    };
    
public:
    SmartKey() = default;
    
public:
    KeyId keyId;
    KeyId auxKeyId;
    Type  type;
    bool  held;
};

#endif
