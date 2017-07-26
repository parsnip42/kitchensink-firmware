#ifndef INCLUDED_EDITMACROSCREEN_H
#define INCLUDED_EDITMACROSCREEN_H

#include "ui/textentrywidget.h"
#include "ui/combowidget.h"

class EventManager;
class KeyEvent;
class KeyEventStage;
class Macro;
class MacroSet;
class Surface;
class Widget;

class EditMacroScreen
{
public:
    EditMacroScreen(Surface&      surface,
                    EventManager& eventManager,
                    MacroSet&     macroSet,
                    Macro&        macro);
    
public:
    void redraw();
    bool processKeyEvent(const KeyEvent& event,
                         KeyEventStage&  next);
private:
    Surface&        mSurface;
    EventManager&   mEventManager;
    MacroSet&       mMacroSet;
    Macro&          mMacro;
    TextEntryWidget mTitleEntry;
    TextEntryWidget mShortcutEntry;
    ComboWidget     mTypeCombo;
    Widget*         mFocused;
};

#endif
