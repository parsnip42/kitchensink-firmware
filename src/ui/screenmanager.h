#ifndef INCLUDED_SCREENMANAGER_H
#define INCLUDED_SCREENMANAGER_H

#include "menudefinitions.h"
#include "ui/screenstack.h"

class Surface;
class EventManager;
class KeyboardState;

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
    
private:
    Surface&        mSurface;
    EventManager&   mEventManager;
    KeyboardState&  mKeyboardState;
    MenuDefinitions mMenuDefinitions;
    ScreenStack     mScreenStack;
};

#endif
