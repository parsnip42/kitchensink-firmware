#ifndef INCLUDED_AUTOREPEAT_H
#define INCLUDED_AUTOREPEAT_H

#include "event/event.h"
#include "event/eventstage.h"
#include "timer.h"
#include "globalconfig.h"

#include <cstdint>

class AutoRepeat : public EventStage
{
public:
    explicit AutoRepeat(Timer&        timer,
                        GlobalConfig& globalConfig,
                        EventStage&   next);

public:
    virtual bool processEvent(const Event& event) override;

    Event activeEvent();

private:
    Timer::Handle mRepeatTimer;
    GlobalConfig& mGlobalConfig;
    Event         mEvent;
    EventStage&   mNext;

private:
    AutoRepeat(const AutoRepeat&) = delete;
    AutoRepeat& operator=(const AutoRepeat&) = delete;
};

#endif
