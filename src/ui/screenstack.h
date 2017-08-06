#ifndef INCLUDED_SCREENSTACK_H
#define INCLUDED_SCREENSTACK_H

#include "keyevent.h"
#include "keyeventstage.h"

class EventManager;
class KeyboardState;
class Surface;

class ScreenStack : public KeyEventStage
{
public:
    ScreenStack(KeyboardState& keyboardState,
                EventManager&  eventManager,
                Surface&       surface,
                KeyEventStage& next);

public:
    virtual void processKeyEvent(const KeyEvent& event) override;

private:
    void processKeyId(const KeyId& keyId);
    
private:
    int            mStackSize;
    KeyboardState& mKeyboardState;
    EventManager&  mEventManager;
    Surface&       mSurface;
    KeyEventStage& mNext;
};


inline
ScreenStack::ScreenStack(KeyboardState& keyboardState,
                         EventManager&  eventManager,
                         Surface&       surface,
                         KeyEventStage& next)
    : mStackSize(0)
    , mKeyboardState(keyboardState)
    , mEventManager(eventManager)
    , mSurface(surface)
    , mNext(next)
{ }

#endif
