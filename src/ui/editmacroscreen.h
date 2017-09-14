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
    EditMacroScreen(Timer&      timer,
                    Macro&      macro,
                    Event       recordEvent,
                    EventStage& next);
    
public:
    virtual bool processEvent(const Event& event) override;

    virtual Widget& rootWidget() override;

private:
    void onRecord();
    
private:
    Macro&                          mMacro;
    LabelledWidget<TextEntryWidget> mTitleEntry;
    LabelledWidget<TextEntryWidget> mShortcutEntry;
    LabelledWidget<ComboWidget>     mTypeCombo;
    ButtonWidget                    mRecordButton;
    HStackWidget::Items<4>          mItems;
    HStackWidget                    mHStackWidget;
    Event                           mRecordEvent;
    EventStage&                     mNext;
};

#endif


