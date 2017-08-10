#ifndef INCLUDED_EDITMACROSCREEN_H
#define INCLUDED_EDITMACROSCREEN_H

#include "ui/textentrywidget.h"
#include "ui/combowidget.h"
#include "ui/hstackwidget.h"
#include "ui/labelledwidget.h"
#include "ui/widgetset.h"
#include "keyeventstage.h"

class ScreenStack;
class Timer;
class KeyEvent;
class MacroSet;
class Widget;

class EditMacroScreen : public KeyEventStage
{
public:
    EditMacroScreen(ScreenStack& screenStack,
                    Timer&       timer,
                    MacroSet&    macroSet,
                    int          macroid);
    
public:
    virtual void processKeyEvent(const KeyEvent& event) override;

    Widget& rootWidget();

private:
    ScreenStack&                    mScreenStack;
    MacroSet&                       mMacroSet;
    int                             mMacroId;
    LabelledWidget<TextEntryWidget> mTitleEntry;
    LabelledWidget<TextEntryWidget> mShortcutEntry;
    LabelledWidget<ComboWidget>     mTypeCombo;
    HStackWidget::Items<3>          mWidgetSet;
    HStackWidget                    mHStackWidget;
};

#endif










