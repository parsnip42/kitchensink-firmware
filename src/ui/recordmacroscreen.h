#ifndef INCLUDED_RECORDMACROSCREEN_H
#define INCLUDED_RECORDMACROSCREEN_H

#include "keyevent.h"
#include "keyeventrecorder.h"
#include "keyeventstage.h"
#include "ui/titlewidget.h"
#include "ui/labelwidget.h"
#include "ui/hsplitwidget.h"

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
    Surface&         mSurface;
    EventManager&    mEventManager;
    Macro&           mMacro;
    KeyEventRecorder mRecorder;
    TitleWidget      mTitleWidget;
    LabelWidget      mLabelWidget;
    HSplitWidget     mHSplit;

private:
    RecordMacroScreen(const RecordMacroScreen&) = delete;
    RecordMacroScreen& operator=(const RecordMacroScreen&) = delete;
};

#endif
