#include "ui/home.h"

#include "keyboardstate.h"
#include "ui/surface.h"
#include "menudefinitions.h"

#include <algorithm>
#include <cstdio>

namespace UI
{

Home::Home(Surface&             surface,
           const KeyboardState& keyboardState,
           EventManager&        eventManager)
    : mSurface(surface)
    , mKeyboardState(keyboardState)
    , mDirty(false)
    , mLastUpdate(0)
    , mEventManager(eventManager)
{
    std::fill(mPaintState.begin(),
              mPaintState.end(),
              0);
}

void Home::poll()
{
    mEventManager.poll(
        [&](const KeyEvent& event,
            KeyEventStage&  next)
        {
            auto keyId(event.keyId);
        
            if (keyId.actionType() == KeyId::ActionType::kMenu)
            {
                if (event.pressed)
                {
                    MenuDefinitions menuDefinitions(mKeyboardState);

                    auto action(event.keyId.value());
                
                    UI::Menu menu(menuDefinitions.getDataSource(action),
                                  mSurface,
                                  mEventManager);

                    menu.poll();
                }
            }
            else
            {
                next.processKeyEvent(event);
            }

            return true;
        });
}

void Home::update()
{
    mDirty = true;
}

void Home::paint()
{
    // if (!mDirty)
    // {
    //     return;
    // }

    // auto now(millis());
    
    // if ((now - mLastUpdate) < 100)
    // {
    //     return;
    // }

    // mLastUpdate = now;
    // mDirty = false;

    // const auto& lockSet(mKeyboardState.lockSet);
    
    // for (int i = 0; i < 12; ++i)
    // {
    //     if (lockSet[i].locked() && (mPaintState[i] == 0))
    //     {
    //         mPaintState[i] = 1;
    //         mDirty = true;
    //     }
    //     else if (!lockSet[i].locked() && (mPaintState[i] > 0))
    //     {
    //         mPaintState[i] = 0;
    //         mDirty = true;
    //     }
    //     else if (mPaintState[i] > 0 && mPaintState[i] < 0xf)
    //     {
    //         ++mPaintState[i];            
    //         mDirty = true;
    //     }
        
    //     mSurface.paintText(((i & 3) * 16),
    //                        52-((i >> 2) * 14),
    //                        lockSet[i].name,
    //                        mPaintState[i], 0);
    // }
}

}
   
