#ifndef INCLUDED_AUTOREPEAT_H
#define INCLUDED_AUTOREPEAT_H

#include "keyid.h"
#include "keystate.h"

class AutoRepeat
{
public:
    explicit AutoRepeat(uint32_t repeatDelay);

public:
    void processKey(const KeyId&    keyId,
                    KeyState::Value state);

    KeyId activeKey() const;
    
private:
    const uint32_t mRepeatDelay;
    KeyId          mKeyId;
    uint32_t       mHeldTime;

};

#endif
