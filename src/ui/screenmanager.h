#ifndef INCLUDED_SCREENMANAGER_H
#define INCLUDED_SCREENMANAGER_H

#include "menudefinitions.h"
#include "ui/screenstack.h"

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
    void pushScreen(const ScreenEvent& screen);
    void popScreen();
    void poll(EventStage& next);

private:
    void launch(const ScreenEvent& screen);
    void launchMenu(int menuId);
    void launchScreen(int screenId);
    void launchEditMacro(MacroSet& macroSet, int macroId);
    void launchRecordMacro(MacroSet& macroSet, int macroId, bool realtime);

    void displayScreen(EventStage& stage,
                       Widget&     content);

    void createTitlePath(const StrOStream& os);
    void createTitle(const ScreenEvent& screen,
                     const StrOStream&  os);
    
    void flush();
    
private:
    Surface&        mSurface;
    EventManager&   mEventManager;
    KeyboardState&  mKeyboardState;
    MenuDefinitions mMenuDefinitions;
    ScreenStack     mScreenStack;
};

#endif
