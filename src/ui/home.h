#ifndef INCLUDED_UI_HOME_H
#define INCLUDED_UI_HOME_H

#include "eventmanager.h"

#include <array>

class KeyboardState;

namespace UI
{

class Surface;

class Home
{
public:
    Home(Surface&             surface,
         const KeyboardState& keyboardState,
         EventManager&        eventManager);

public:
    void poll();
    void update();
    void paint();
    
private:
    Surface&             mSurface;
    const KeyboardState& mKeyboardState;
    std::array<int, 30>  mPaintState;
    bool                 mDirty;
    uint32_t             mLastUpdate;
    EventManager&        mEventManager;
    
private:
    Home(const Home&) = delete;
    Home& operator=(const Home&) = delete;
};

}

#endif
