#ifndef INCLUDED_UI_HOME_H
#define INCLUDED_UI_HOME_H

#include "keyeventstage.h"
#include "keyeventbuffer.h"
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
         KeyEventBuffer&      buffer,
         KeyEventStage&       next);

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
    KeyEventBuffer&      mBuffer;
    KeyEventStage&       mNext;
    
private:
    Home(const Home&) = delete;
    Home& operator=(const Home&) = delete;
};

}

#endif
