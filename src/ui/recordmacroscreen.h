#ifndef INCLUDED_RECORDMACROSCREEN_H
#define INCLUDED_RECORDMACROSCREEN_H

#include "keyevent.h"
#include "keyeventrecorder.h"
#include "keyeventstage.h"

class Macro;
class EventManager;
class Surface;

class RecordMacroScreen : public KeyEventStage
{    
public:
    RecordMacroScreen(Surface&       surface,
                      EventManager&  eventManager,
                      Macro&         macro,
                      bool           realtime);

public:
    virtual void processKeyEvent(const KeyEvent& event);

    void poll();
    
private:
    void redraw();
    
private:
    Surface&         mSurface;
    EventManager&    mEventManager;
    Macro&           mMacro;
    KeyEventRecorder mRecorder;
    
private:
    RecordMacroScreen(const RecordMacroScreen&) = delete;
    RecordMacroScreen& operator=(const RecordMacroScreen&) = delete;
};


inline
RecordMacroScreen::RecordMacroScreen(Surface&       surface,
                                     EventManager&  eventManager,
                                     Macro&         macro,
                                     bool           realtime)
    : mSurface(surface)
    , mEventManager(eventManager)
    , mMacro(macro)
    , mRecorder(realtime)
{ }

#endif
