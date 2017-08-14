#ifndef INCLUDED_EDITMACROSCREEN_H
#define INCLUDED_EDITMACROSCREEN_H

#include "ui/textentrywidget.h"
#include "ui/combowidget.h"
#include "ui/hstackwidget.h"
#include "ui/labelledwidget.h"
#include "event/eventstage.h"

class ScreenStack;
class Timer;
class Event;
class MacroSet;
class Widget;

class EditMacroScreen : public EventStage
{
public:
    EditMacroScreen(ScreenStack& screenStack,
                    Timer&       timer,
                    MacroSet&    macroSet,
                    int          macroid);
    
public:
    virtual void processEvent(const Event& event) override;

    Widget& rootWidget();

private:
    ScreenStack&                    mScreenStack;
    MacroSet&                       mMacroSet;
    int                             mMacroId;
    LabelledWidget<TextEntryWidget> mTitleEntry;
    LabelledWidget<TextEntryWidget> mShortcutEntry;
    LabelledWidget<ComboWidget>     mTypeCombo;
    HStackWidget::Items<3>          mItems;
    HStackWidget                    mHStackWidget;
};

#endif










