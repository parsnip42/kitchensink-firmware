#include "ui/home.h"

#include "keyboardstate.h"
#include "ui/surface.h"

#include <algorithm>
#include <cstdio>
#include <elapsedMillis.h>

namespace UI
{

Home::Home(Surface&             surface,
           const KeyboardState& keyboardState)
    : mSurface(surface)
    , mKeyboardState(keyboardState)
    , mDirty(false)
    , mLastUpdate(0)
{
    std::fill(mPaintState.begin(),
              mPaintState.end(),
              0);
}

void Home::update()
{
    mDirty = true;
}

void Home::paint()
{
    if (!mDirty)
    {
        return;
    }

    auto now(millis());
    
    if ((now - mLastUpdate) < 100)
    {
        return;
    }

    mLastUpdate = now;
    mDirty = false;

    const auto& lockSet(mKeyboardState.lockSet);
    
    for (int i = 0; i < 12; ++i)
    {
        if (lockSet[i].locked() && (mPaintState[i] == 0))
        {
            mPaintState[i] = 1;
            mDirty = true;
        }
        else if (!lockSet[i].locked() && (mPaintState[i] > 0))
        {
            mPaintState[i] = 0;
            mDirty = true;
        }
        else if (mPaintState[i] > 0 && mPaintState[i] < 0xf)
        {
            ++mPaintState[i];            
            mDirty = true;
        }
        
        mSurface.paintText(((i & 3) * 16),
                           52-((i >> 2) * 14),
                           lockSet[i].name,
                           mPaintState[i], 0);
    }
}

}
   
