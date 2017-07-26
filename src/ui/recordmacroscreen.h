#ifndef INCLUDED_RECORDMACROSCREEN_H
#define INCLUDED_RECORDMACROSCREEN_H

#include "types/strref.h"
#include "keyevent.h"
#include "keyeventrecorder.h"

class Macro;
class EventManager;
class Surface;

class RecordMacroScreen
{    
public:
    RecordMacroScreen(Surface&       surface,
                      EventManager&  eventManager,
                      Macro&         macro,
                      bool           realtime);

public:
    void redraw();
    bool processKeyEvent(const KeyEvent& event,
                         KeyEventStage&  next);
    
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
