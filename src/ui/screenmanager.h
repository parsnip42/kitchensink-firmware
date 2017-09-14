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
class EntropyPool;

class ScreenManager
{    
public:
    ScreenManager(Surface&       surface,
                  EventManager&  eventManager,
                  KeyboardState& keyboardState,
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
    Surface&        mSurface;
    EventManager&   mEventManager;
    KeyboardState&  mKeyboardState;
    EntropyPool&    mEntropyPool;
    MenuDefinitions mMenuDefinitions;

public:
    CircularBuffer<ScreenEvent, 12> mScreenEventQueue;
};

#endif
