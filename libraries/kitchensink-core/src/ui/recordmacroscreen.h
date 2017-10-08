#ifndef INCLUDED_RECORDMACROSCREEN_H
#define INCLUDED_RECORDMACROSCREEN_H

#include "eventrecorder.h"
#include "event/eventstage.h"
#include "ui/labelwidget.h"
#include "ui/screen.h"
#include "timer.h"

class Timer;
class Macro;

class RecordMacroScreen : public Screen
{    
public:
    RecordMacroScreen(Timer&      timer,
                      Macro&      macro,
                      EventStage& next);

public:
    virtual bool processEvent(const Event& event);

    Widget& rootWidget();
    
private:
    Macro&        mMacro;
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
