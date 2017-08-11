#ifndef INCLUDED_SMARTKEY_H
#define INCLUDED_SMARTKEY_H

#include "keyid.h"
#include "types/strbuf.h"
#include "config.h"

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
    StrBuf<Config::kSmartKeyNameLen> name;
    KeyId                            keyId;
    KeyId                            auxKeyId;
    Type                             type;
    bool                             enabled;
};


inline
SmartKey::SmartKey()
    : type(kToggle)
    , enabled(false)
{ }

#endif
