#ifndef INCLUDED_UI_HOME_H
#define INCLUDED_UI_HOME_H

#include "keyeventpipeline.h"
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
         KeyEventPipeline&    pipeline);

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
    KeyEventPipeline&    mPipeline;
    
private:
    Home(const Home&) = delete;
    Home& operator=(const Home&) = delete;
};

}

#endif
