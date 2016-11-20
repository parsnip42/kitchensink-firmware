#ifndef INCLUDED_AUTOREPEAT_H
#define INCLUDED_AUTOREPEAT_H

#include "keyevent.h"

#include <cstdint>

class AutoRepeat
{
public:
    explicit AutoRepeat(uint32_t repeatDelay);

public:
    void processEvent(const KeyEvent& keyEvent);

    KeyId activeKey();
    
private:
    const uint32_t mRepeatDelay;
    KeyId          mKeyId;
    uint32_t       mHeldTime;

};

#endif
