#ifndef INCLUDED_SMARTKEY_H
#define INCLUDED_SMARTKEY_H

#include "event/event.h"
#include "types/strbuf.h"
#include "config.h"

class SmartKey
{
public:
    enum Type : uint8_t
    {
        // Press to toggle key state.
        kToggle            = 0,

        // Press to toggle key state, release after another key is released.
        kToggleAutoRelease = 1,

        // Normal hold behaviour, but key is released when another key is
        // released.
        kHoldAutoRelease   = 2,

        // Pressing presses and releases one key, releasing presses and releases
        // the aux.
        kPair              = 3,
        
        // Normal hold behaviour, but if another key isn't pressed in the
        // meantime, the aux is pressed and released. Can be used to implement
        // space cadet shift.
        kHoldOrTap         = 4
    };
    
public:
    SmartKey();
    
public:
    StrBuf<Config::kSmartKeyNameLen> name;
    Event                            event;
    Event                            auxEvent;
    Type                             type;
    bool                             enabled;
};


inline
SmartKey::SmartKey()
    : type(kToggle)
    , enabled(false)
{ }

#endif
