#ifndef INCLUDED_AUTOREPEAT_H
#define INCLUDED_AUTOREPEAT_H

#include "keyid.h"

#include <cstdint>

class AutoRepeat
{
public:
    explicit AutoRepeat(uint32_t repeatDelay);

public:
    void processKey(const KeyId& keyId,
                    bool         pressed);

    KeyId activeKey();
    
private:
    const uint32_t mRepeatDelay;
    KeyId          mKeyId;
    uint32_t       mHeldTime;

};

#endif
