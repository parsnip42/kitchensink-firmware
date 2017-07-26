#ifndef INCLUDED_EDITMACROSCREEN_H
#define INCLUDED_EDITMACROSCREEN_H

class EventManager;
class KeyEvent;
class KeyEventStage;
class Macro;
class Surface;

class EditMacroScreen
{
public:
    EditMacroScreen(Surface&      surface,
                    EventManager& eventManager,
                    Macro&        macro);
    
public:
    void redraw();
    bool processKeyEvent(const KeyEvent& event,
                         KeyEventStage&  next);
private:
    Surface&      mSurface;
    EventManager& mEventManager;
    Macro&        mMacro;
};

#endif
