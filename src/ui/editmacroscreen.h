#ifndef INCLUDED_EDITMACROSCREEN_H
#define INCLUDED_EDITMACROSCREEN_H

#include "ui/textentrywidget.h"
#include "ui/combowidget.h"
#include "ui/labelledwidget.h"
#include "ui/listwidget.h"
#include "ui/titlewidget.h"
#include "ui/hsplitwidget.h"
#include "ui/widgetset.h"
#include "keyeventstage.h"

#include <tuple>

class EventManager;
class KeyEvent;
class Macro;
class MacroSet;
class Surface;
class Widget;

class EditMacroScreen : public KeyEventStage
{
public:
    EditMacroScreen(Timer&    timer,
                    MacroSet& macroSet,
                    Macro&    macro);
    
public:
    virtual void processKeyEvent(const KeyEvent& event) override;

    Widget& rootWidget();

private:
    MacroSet&                       mMacroSet;
    Macro&                          mMacro;
    TitleWidget                     mTitleWidget;
    LabelledWidget<TextEntryWidget> mTitleEntry;
    LabelledWidget<TextEntryWidget> mShortcutEntry;
    LabelledWidget<ComboWidget>     mTypeCombo;
    WidgetSet<3>                    mWidgetSet;
    ListWidget                      mListWidget;
    HSplitWidget                    mHSplit;
};

#endif
