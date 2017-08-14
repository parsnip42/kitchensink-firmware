#ifndef INCLUDED_EVENTMANAGER_H
#define INCLUDED_EVENTMANAGER_H

#include "keyeventbuffer.h"
#include "eventstage.h"
#include "event/event.h"
#include "keysource.h"
#include "ledsource.h"
#include "timer.h"
#include "topleveleventstage.h"

#include <cstdint>

class EventManager : public EventStage
{
public:
    EventManager(Timer&              nTimer,
                 KeySource&          keySource,
                 LedSource&          ledSource,
                 EventStage&         input,
                 ToplevelEventStage& toplevel,
                 EventStage&         nDefaultOutput);

public:
    virtual void processEvent(const Event& event) override;

    void poll(EventStage& output);
    void flush(EventStage& output);
    
public:
    Timer&      timer;
    EventStage& defaultOutput;
    
private:
    uint32_t nowMs() const;
    
private:
    EventBuffer         mBuffer;
    KeySource&          mKeySource;
    LedSource&          mLedSource;
    EventStage&         mInput;
    ToplevelEventStage& mToplevel;

private:
    EventManager(const EventManager&) = delete;
    EventManager& operator=(const EventManager&) = delete;
    
private:
    friend class RefocusGuard;
};

#endif








