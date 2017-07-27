#ifndef INCLUDED_SMARTKEY_H
#define INCLUDED_SMARTKEY_H

#include "keyid.h"
#include "types/strbuf.h"

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
    SmartKey();
    
public:
    StrBuf<12> name;
    KeyId      keyId;
    KeyId      auxKeyId;
    Type       type;
    bool       triggered;
};

inline
SmartKey::SmartKey()
    : type(kToggle)
    , triggered(false)
{ }

#endif
