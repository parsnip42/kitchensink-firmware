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
    void poll();

private:
    bool transient(const ScreenEvent& screenEvent) const;

    void launch(const ScreenEvent& screen,
                EventStage&        next);

    void launchHome();

    void launchMenu(int                menuId,
                    const ScreenEvent& sourceEvent,
                    EventStage&        next);
    
    void launchScreen(int                screenId,
                      const ScreenEvent& sourceEvent);

    void launchEditMacro(MacroSet&          macroSet,
                         int                macroId,
                         const ScreenEvent& sourceEvent);

    void launchRecordMacro(MacroSet&          macroSet,
                           int                macroId,
                           bool               realtime,
                           const ScreenEvent& sourceEvent);

    void launchEditLayer(int                layerId,
                         const ScreenEvent& sourceEvent);

    void launchEditMultiKey(int                multiKeyId,
                            const ScreenEvent& sourceEvent);
    
    void launchEditSmartKey(int                smartKeyId,
                            const ScreenEvent& sourceEvent);

    void displayScreen(const StrRef&      title,
                       Screen&            screen,
                       const ScreenEvent& sourceEvent);
    
private:
    Surface&        mSurface;
    EventManager&   mEventManager;
    KeyboardState&  mKeyboardState;
    MenuDefinitions mMenuDefinitions;

public:
    CircularBuffer<ScreenEvent, 12> mScreenEventQueue;
};

#endif
