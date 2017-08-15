#ifndef INCLUDED_RECORDMACROSCREEN_H
#define INCLUDED_RECORDMACROSCREEN_H

#include "eventrecorder.h"
#include "event/eventstage.h"
#include "timer.h"
#include "ui/labelwidget.h"

class ScreenStack;
class Timer;
class MacroSet;

class RecordMacroScreen : public EventStage
{    
public:
    RecordMacroScreen(ScreenStack& screenStack,
                      Timer&       timer,
                      MacroSet&    macroSet,
                      int          macroId,
                      bool         realtime,
                      EventStage&  next);

public:
    virtual void processEvent(const Event& event);

    Widget& rootWidget();
    
private:
    ScreenStack&  mScreenStack;
    MacroSet&     mMacroSet;
    int           mMacroId;
    EventRecorder mRecorder;
    LabelWidget   mLabelWidget;
    Timer::Handle mFlashTimer;
    bool          mFlash;
    EventStage&   mNext;
    
private:
    RecordMacroScreen(const RecordMacroScreen&) = delete;
    RecordMacroScreen& operator=(const RecordMacroScreen&) = delete;
};

#endif
