#ifndef INCLUDED_SCREENSTACK_H
#define INCLUDED_SCREENSTACK_H

#include "keyevent.h"

class EventManager;
class KeyboardState;
class Surface;

class ScreenStack
{
public:
    ScreenStack(KeyboardState& keyboardState,
                EventManager&  eventManager,
                Surface&       surface);

public:
    bool processEvent(const KeyEvent& event);
    
private:
    int            mStackSize;
    KeyboardState& mKeyboardState;
    EventManager&  mEventManager;
    Surface&       mSurface;
};


inline
ScreenStack::ScreenStack(KeyboardState& keyboardState,
                         EventManager&  eventManager,
                         Surface&       surface)
    : mStackSize(0)
    , mKeyboardState(keyboardState)
    , mEventManager(eventManager)
    , mSurface(surface)
{ }

#endif /* INCLUDED_SCREENSTACK_H */
