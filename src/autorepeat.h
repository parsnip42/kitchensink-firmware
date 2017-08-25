#ifndef INCLUDED_AUTOREPEAT_H
#define INCLUDED_AUTOREPEAT_H

#include "event/event.h"
#include "event/eventstage.h"
#include "timer.h"

#include <cstdint>

class AutoRepeat : public EventStage
{
public:
    explicit AutoRepeat(Timer&         timer,
                        EventStage& next);

public:
    virtual bool processEvent(const Event& event) override;

    Event activeEvent();

public:
    uint32_t repeatDelay;
    uint32_t repeatRate;
    
private:
    Timer::Handle mRepeatTimer;
    Event         mEvent;
    EventStage&   mNext;

private:
    AutoRepeat(const AutoRepeat&) = delete;
    AutoRepeat& operator=(const AutoRepeat&) = delete;
};

#endif
