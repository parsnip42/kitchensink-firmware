#ifndef INCLUDED_SCREENMANAGER_H
#define INCLUDED_SCREENMANAGER_H

#include "ui/menudefinitions.h"
#include "ui/screen.h"
#include "ui/surface.h"
#include "event/screenevent.h"
#include "event/eventstage.h"
#include "types/circularbuffer.h"

class Display;
class EntropyPool;
class EventManager;
class KeyHardware;
class KeyboardState;
class ScreenEvent;
class StrOStream;
class TimerManager;

class ScreenManager
{    
public:
    ScreenManager(Display&       display,
                  EventManager&  eventManager,
                  TimerManager&  timerManager,
                  KeyboardState& keyboardState,
                  KeyHardware&   keyHardware,
                  EntropyPool&   entropyPool);
    
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

    void launchEditMacro(Macro&             macro,
                         Event              recordEvent,
                         const ScreenEvent& sourceEvent);

    void launchRecordMacro(Macro&             macro,
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
    Surface         mSurface;
    EventManager&   mEventManager;
    TimerManager&   mTimerManager;
    KeyboardState&  mKeyboardState;
    KeyHardware&    mKeyHardware;
    EntropyPool&    mEntropyPool;
    MenuDefinitions mMenuDefinitions;

public:
    CircularBuffer<ScreenEvent, 12> mScreenEventQueue;
};

#endif
