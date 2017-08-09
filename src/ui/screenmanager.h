#ifndef INCLUDED_SCREENMANAGER_H
#define INCLUDED_SCREENMANAGER_H

#include "menudefinitions.h"
#include "ui/screenstack.h"

class Surface;
class EventManager;
class KeyboardState;
class StrOStream;

class ScreenManager
{    
public:
    ScreenManager(Surface&       surface,
                  EventManager&  eventManager,
                  KeyboardState& keyboardState);
    
public:
    void pushScreen(const ScreenId& screen);
    void popScreen();
    void poll(KeyEventStage& next);

private:
    void launch(const ScreenId& screen);
    void launchMenu(int menuId);
    void launchScreen(int screenId);
    void launchEditMacro(MacroSet& macroSet, int macroId);
    void launchRecordMacro(MacroSet& macroSet, int macroId, bool realtime);

    void displayScreen(KeyEventStage& stage,
                       Widget&        content);

    void createTitlePath(const StrOStream& os);
    void createTitle(const ScreenId&   screenId,
                     const StrOStream& os);
    
    void flush();
    
private:
    Surface&        mSurface;
    EventManager&   mEventManager;
    KeyboardState&  mKeyboardState;
    MenuDefinitions mMenuDefinitions;
    ScreenStack     mScreenStack;
};

#endif
