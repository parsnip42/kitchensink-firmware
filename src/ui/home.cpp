#include "ui/home.h"

#include "modifierset.h"
#include "ui/surface.h"

#include <algorithm>
#include <cstdio>
#include <elapsedMillis.h>

namespace UI
{

Home::Home(Surface&           surface,
           const ModifierSet& modifierSet)
    : mSurface(surface)
    , mModifierSet(modifierSet)
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

    // char tempStr[12];
    // snprintf(tempStr, sizeof(tempStr), "%lu", mLastUpdate);
    // mSurface.paintText(28, 0, tempStr);
                       
    for (int i = 0; i < 10; ++i)
    {
        if (mModifierSet[i].locked() && (mPaintState[i] == 0))
        {
            mPaintState[i] = 1;
            mDirty = true;
        }
        else if (!mModifierSet[i].locked() && (mPaintState[i] > 0))
        {
            mPaintState[i] = 0;
            mDirty = true;
        }
        else if (mPaintState[i] > 0 && mPaintState[i] < 0xf)
        {
            ++mPaintState[i];            
            mDirty = true;
        }
        
        const char* text(mModifierSet[i].name());

        auto offset(i);
        mSurface.paintText(((offset&3) * 16), 52-((offset >> 2) * 14),
                           text, mPaintState[i], 0);
    }
}

}
   
