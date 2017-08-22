#ifndef INCLUDED_EDITMACROSCREEN_H
#define INCLUDED_EDITMACROSCREEN_H

#include "ui/textentrywidget.h"
#include "ui/combowidget.h"
#include "ui/hstackwidget.h"
#include "ui/labelledwidget.h"
#include "ui/screen.h"
#include "event/eventstage.h"

class ScreenStack;
class Timer;
class Event;
class MacroSet;
class Widget;

class EditMacroScreen : public Screen
{
public:
    EditMacroScreen(Timer&      timer,
                    MacroSet&   macroSet,
                    int         macroid,
                    EventStage& next);
    
public:
    virtual void processEvent(const Event& event) override;

    virtual Widget& rootWidget() override;

private:
    MacroSet&                       mMacroSet;
    int                             mMacroId;
    LabelledWidget<TextEntryWidget> mTitleEntry;
    LabelledWidget<TextEntryWidget> mShortcutEntry;
    LabelledWidget<ComboWidget>     mTypeCombo;
    HStackWidget::Items<3>          mItems;
    HStackWidget                    mHStackWidget;
    EventStage&                     mNext;
};

#endif










