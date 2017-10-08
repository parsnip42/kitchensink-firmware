#ifndef INCLUDED_EDITMACROSCREEN_H
#define INCLUDED_EDITMACROSCREEN_H

#include "event/eventstage.h"
#include "ui/buttonwidget.h"
#include "ui/combowidget.h"
#include "ui/hstackwidget.h"
#include "ui/labelledwidget.h"
#include "ui/screen.h"
#include "ui/textentrywidget.h"

class ScreenStack;
class Timer;
class Event;
class Macro;
class Widget;

class EditMacroScreen : public Screen
{
public:
    EditMacroScreen(TimerManager&      timer,
                    Macro&      macro,
                    Event       recordEvent,
                    EventStage& next);
    
public:
    virtual bool processEvent(const Event& event) override;
    virtual Widget& rootWidget() override;
    virtual void screenExit() override;

private:
    void apply();
    void onRecord();
    
private:
    Macro&                          mMacro;
    LabelledWidget<TextEntryWidget> mTitleEntry;
    LabelledWidget<TextEntryWidget> mShortcutEntry;
    LabelledWidget<ComboWidget>     mTypeCombo;
    HStackWidget::Items<3>          mItems;
    HStackWidget                    mHStackWidget;
    Event                           mRecordEvent;
    EventStage&                     mNext;
};

#endif


