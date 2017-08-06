#ifndef INCLUDED_AUTOREPEAT_H
#define INCLUDED_AUTOREPEAT_H

#include "keyevent.h"
#include "keyeventstage.h"
#include "timer.h"

#include <cstdint>

class AutoRepeat : public KeyEventStage
{
public:
    explicit AutoRepeat(Timer&         timer,
                        KeyEventStage& next);

public:
    virtual void processKeyEvent(const KeyEvent& event) override;

    KeyId activeKey();

public:
    uint32_t repeatDelay;
    uint32_t repeatRate;
    
private:
    Timer::Handle  mRepeatTimer;
    KeyId          mKeyId;
    KeyEventStage& mNext;

private:
    AutoRepeat(const AutoRepeat&) = delete;
    AutoRepeat& operator=(const AutoRepeat&) = delete;
};

#endif
