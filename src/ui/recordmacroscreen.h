#ifndef INCLUDED_RECORDMACROSCREEN_H
#define INCLUDED_RECORDMACROSCREEN_H

#include "keyevent.h"
#include "keyeventrecorder.h"
#include "keyeventstage.h"
#include "timer.h"
#include "ui/titlewidget.h"
#include "ui/labelwidget.h"
#include "ui/hsplitwidget.h"

class ScreenStack;
class Timer;
class MacroSet;

class RecordMacroScreen : public KeyEventStage
{    
public:
    RecordMacroScreen(ScreenStack&   screenStack,
                      Timer&         timer,
                      MacroSet&      macroSet,
                      int            macroId,
                      bool           realtime,
                      KeyEventStage& next);

public:
    virtual void processKeyEvent(const KeyEvent& event);

    Widget& rootWidget();
    
private:
    ScreenStack&     mScreenStack;
    MacroSet&        mMacroSet;
    int              mMacroId;
    KeyEventRecorder mRecorder;
    TitleWidget      mTitleWidget;
    LabelWidget      mLabelWidget;
    HSplitWidget     mHSplit;
    Timer::Handle    mFlashTimer;
    bool             mFlash;
    KeyEventStage&   mNext;
    
private:
    RecordMacroScreen(const RecordMacroScreen&) = delete;
    RecordMacroScreen& operator=(const RecordMacroScreen&) = delete;
};

#endif
