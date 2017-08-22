#ifndef INCLUDED_SCREENMANAGER_H
#define INCLUDED_SCREENMANAGER_H

#include "ui/menudefinitions.h"
#include "event/screenevent.h"

class Surface;
class EventManager;
class KeyboardState;
class StrOStream;
class ScreenEvent;

class ScreenManager
{    
public:
    ScreenManager(Surface&       surface,
                  EventManager&  eventManager,
                  KeyboardState& keyboardState);
    
public:
    // virtual void processEvent(const Event& event) override;

    void poll(EventStage& next);

private:
    void launch(const ScreenEvent& screen);
    void launchHome();
    void launchMenu(int menuId);
    void launchScreen(int screenId);
    void launchEditMacro(MacroSet& macroSet, int macroId);
    void launchRecordMacro(MacroSet& macroSet, int macroId, bool realtime);

    void displayScreen(const StrRef& title,
                       Screen&       screen);
    
private:
    Surface&        mSurface;
    EventManager&   mEventManager;
    KeyboardState&  mKeyboardState;
    MenuDefinitions mMenuDefinitions;

public:
    ScreenEvent     mCurrent;
};

#endif








