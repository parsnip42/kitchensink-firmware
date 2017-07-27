#ifndef INCLUDED_EDITMACROSCREEN_H
#define INCLUDED_EDITMACROSCREEN_H

#include "ui/textentrywidget.h"
#include "ui/combowidget.h"
#include "keyeventstage.h"

class EventManager;
class KeyEvent;
class Macro;
class MacroSet;
class Surface;
class Widget;

class EditMacroScreen : public KeyEventStage
{
public:
    EditMacroScreen(Surface&      surface,
                    EventManager& eventManager,
                    MacroSet&     macroSet,
                    Macro&        macro);
    
public:
    virtual void processKeyEvent(const KeyEvent& event) override;
    
    void poll();

private:
    void redraw();
    
private:
    Surface&        mSurface;
    EventManager&   mEventManager;
    MacroSet&       mMacroSet;
    Macro&          mMacro;
    TextEntryWidget mTitleEntry;
    TextEntryWidget mShortcutEntry;
    ComboWidget     mTypeCombo;
    Widget*         mFocused;
    bool            mQuit;
};

#endif
