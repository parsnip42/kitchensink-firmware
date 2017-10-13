#ifndef INCLUDED_EVENTMANAGER_H
#define INCLUDED_EVENTMANAGER_H

#include "event/eventbuffer.h"
#include "event/eventstage.h"
#include "event/event.h"
#include "timer/timermanager.h"
#include "topleveleventstage.h"

#include <cstdint>

class EventSource;

class EventManager : public EventStage
{
public:
    EventManager(TimerManager&       nTimerManager,
                 EventSource&        nEventSource,
                 EventStage&         input,
                 ToplevelEventStage& toplevel,
                 EventStage&         nDefaultOutput);

public:
    virtual bool processEvent(const Event& event) override;

    void poll(EventStage& output);
    void flush(EventStage& output);
    
public:
    TimerManager& timerManager;
    EventStage&   defaultOutput;
    
private:
    EventSource&        mEventSource;
    EventBuffer         mBuffer;
    EventStage&         mInput;
    ToplevelEventStage& mToplevel;

private:
    EventManager(const EventManager&) = delete;
    EventManager& operator=(const EventManager&) = delete;
};

#endif








