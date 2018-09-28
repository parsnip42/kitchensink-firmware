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

    void launchScreen(int                screenId,
                      const ScreenEvent& sourceEvent);


    void displayScreen(const StrRef&      title,
                       Screen&            screen,
                       const ScreenEvent& sourceEvent);

    ////////////////////////////////////////
    
    void launchHome();
    void launchMenu(int                menuId,
                    const ScreenEvent& sourceEvent,
                    EventStage&        next);
    void launchRecordMacroScreen(Macro&             macro,
                                 const ScreenEvent& sourceEvent);
    void launchEditLayerScreen(int                layerId,
                               const ScreenEvent& sourceEvent);
    void launchEditMultiKeyScreen(int                multiKeyId,
                                  const ScreenEvent& sourceEvent);
    void launchEditSmartKeyScreen(int                smartKeyId,
                                  const ScreenEvent& sourceEvent);
    void launchEditMacroScreen(Macro&             macro,
                               Event              recordEvent,
                               const ScreenEvent& sourceEvent);
    void launchGlobalConfigScreen(const ScreenEvent& sourceEvent);
    void launchStatusScreen(const ScreenEvent& sourceEvent);
    void launchCryptoScreen(const ScreenEvent& sourceEvent);
    void launchEventStreamScreen(const ScreenEvent& sourceEvent);
    void launchMacroUnlockScreen(const ScreenEvent& sourceEvent);
    void launchMacroSaveScreen(const ScreenEvent& sourceEvent);
    void launchInitSecureMacroScreen(const ScreenEvent& sourceEvent);

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

private:
    ScreenManager(const ScreenManager&) = delete;
    ScreenManager& operator=(const ScreenManager&) = delete;
};

#endif
