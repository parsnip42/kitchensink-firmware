#ifndef INCLUDED_EVENTMANAGER_H
#define INCLUDED_EVENTMANAGER_H

#include "keyeventbuffer.h"
#include "keyeventstage.h"
#include "keyeventsource.h"
#include "keyevent.h"
#include "keyprocessor.h"
#include "timer.h"
#include "topleveleventstage.h"

#include <cstdint>

class EventManager : public KeyEventStage
{
public:
    class RefocusGuard
    {
    public:
        explicit RefocusGuard(EventManager& eventManager);
        
        ~RefocusGuard();
        
    private:
        EventManager& mEventManager;

    private:
        RefocusGuard(const RefocusGuard&);
        RefocusGuard& operator=(const RefocusGuard&);
    };
    
public:
    EventManager(Timer&              nTimer,
                 KeyProcessor&       source,
                 KeyEventStage&      input,
                 ToplevelEventStage& toplevel,
                 KeyEventStage&      nDefaultOutput);

public:
    virtual void processKeyEvent(const KeyEvent& event) override;

    void poll(KeyEventStage& output);
    void untilKeysReleased();
    
public:
    Timer&         timer;
    KeyEventStage& defaultOutput;
    
private:
    uint32_t nowMs() const;
    
private:
    KeyEventBuffer      mBuffer;
    KeyProcessor&       mSource;
    KeyEventStage&      mInput;
    ToplevelEventStage& mToplevel;

private:
    EventManager(const EventManager&) = delete;
    EventManager& operator=(const EventManager&) = delete;
    
private:
    friend class RefocusGuard;
};

#endif








