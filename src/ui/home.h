#ifndef INCLUDED_UI_HOME_H
#define INCLUDED_UI_HOME_H

#include "modifierset.h"

#include <array>

namespace UI
{

class Surface;

class Home
{
public:
    Home(Surface&          surface,
         const ModifierSet& modifierSet);

public:
    void update();
    void paint();
    
private:
    Surface&            mSurface;
    const ModifierSet&  mModifierSet;
    std::array<int, 30> mPaintState;
    bool                mDirty;
    uint32_t            mLastUpdate;
    
private:
    Home(const Home&) = delete;
    Home& operator=(const Home&) = delete;
};

}

#endif
