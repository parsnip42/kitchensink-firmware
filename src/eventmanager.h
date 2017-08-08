#ifndef INCLUDED_EVENTMANAGER_H
#define INCLUDED_EVENTMANAGER_H

#include "keyeventbuffer.h"
#include "keyeventstage.h"
#include "keyeventsource.h"
#include "keyevent.h"
#include "keysource.h"
#include "timer.h"
#include "topleveleventstage.h"

#include <cstdint>

class EventManager : public KeyEventStage
{
public:
    EventManager(Timer&              nTimer,
                 KeySource&          source,
                 KeyEventStage&      input,
                 ToplevelEventStage& toplevel,
                 KeyEventStage&      nDefaultOutput);

public:
    virtual void processKeyEvent(const KeyEvent& event) override;

    void poll(KeyEventStage& output);
    void flush(KeyEventStage& output);
    
public:
    Timer&         timer;
    KeyEventStage& defaultOutput;
    
private:
    uint32_t nowMs() const;
    
private:
    KeyEventBuffer      mBuffer;
    KeySource&          mSource;
    KeyEventStage&      mInput;
    ToplevelEventStage& mToplevel;

private:
    EventManager(const EventManager&) = delete;
    EventManager& operator=(const EventManager&) = delete;
    
private:
    friend class RefocusGuard;
};

#endif








