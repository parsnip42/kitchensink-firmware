#ifndef INCLUDED_AUTOREPEAT_H
#define INCLUDED_AUTOREPEAT_H

#include "keyevent.h"

#include <cstdint>

class AutoRepeat
{
public:
    explicit AutoRepeat(uint32_t repeatDelay = 660,
                        uint32_t repeatRate = 40);

public:
    void processEvent(const KeyEvent& keyEvent);

    KeyId activeKey();
    
private:
    const uint32_t mRepeatDelay;
    const uint32_t mRepeatRate;
    KeyId          mKeyId;
    uint32_t       mNextTime;

};

#endif
