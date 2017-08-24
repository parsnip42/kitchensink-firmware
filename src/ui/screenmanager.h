#ifndef INCLUDED_SCREENMANAGER_H
#define INCLUDED_SCREENMANAGER_H

#include "ui/menudefinitions.h"
#include "ui/screen.h"
#include "event/screenevent.h"
#include "event/eventstage.h"
#include "types/circularbuffer.h"

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
    void poll(EventStage& next);

private:
    void launch(const ScreenEvent& screen,
                EventStage&        next);

    void launchHome();

    void launchMenu(int         menuId,
                    EventStage& next);
    
    void launchScreen(int screenId);
    void launchEditMacro(MacroSet& macroSet, int macroId);
    void launchRecordMacro(MacroSet& macroSet, int macroId, bool realtime);
    void launchEditLayer(int layerId);
    void launchEditMultiKey(int multiKeyId);
    void launchEditSmartKey(int smartKeyId);

    void displayScreen(const StrRef& title,
                       Screen&       screen,
                       bool          transient = true);
    
private:
    Surface&        mSurface;
    EventManager&   mEventManager;
    KeyboardState&  mKeyboardState;
    MenuDefinitions mMenuDefinitions;

public:
    CircularBuffer<ScreenEvent, 12> mScreenEventQueue;
};

#endif








