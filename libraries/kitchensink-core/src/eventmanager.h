#ifndef INCLUDED_EVENTMANAGER_H
#define INCLUDED_EVENTMANAGER_H

#include "event/eventbuffer.h"
#include "event/eventstage.h"
#include "event/event.h"
#include "keysource.h"
#include "ledsource.h"
#include "timermanager.h"
#include "topleveleventstage.h"

#include <cstdint>

class EventManager : public EventStage
{
public:
    EventManager(TimerManager&              nTimer,
                 KeySource&          nKeySource,
                 LedSource&          ledSource,
                 EventStage&         input,
                 ToplevelEventStage& toplevel,
                 EventStage&         nDefaultOutput);

public:
    virtual bool processEvent(const Event& event) override;

    void poll(EventStage& output);
    void flush(EventStage& output);
    
public:
    TimerManager&      timer;
    KeySource&  keySource;
    EventStage& defaultOutput;
    
private:
    EventBuffer         mBuffer;
    LedSource&          mLedSource;
    EventStage&         mInput;
    ToplevelEventStage& mToplevel;

private:
    EventManager(const EventManager&) = delete;
    EventManager& operator=(const EventManager&) = delete;
};

#endif








