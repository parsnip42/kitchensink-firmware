#include "ui/screenstack.h"

#include "keyboardstate.h"
#include "menudefinitions.h"
#include "ui/menu.h"

#include "ui/editmacroscreen.h"

bool ScreenStack::processEvent(const KeyEvent& event)
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

            menu.redraw();
            
            mEventManager.poll(
                [&](const KeyEvent& event,
                    KeyEventStage&  next)
                {
                    return menu.processKeyEvent(event, next);
                });

            mSurface.clear();
        }

        return true;
    }


    if (keyId.actionType() == KeyId::ActionType::kEditMacro)
    {
        if (event.pressed)
        {
            auto macroIndex(keyId.value());
            auto& macro(mKeyboardState.macroSet[macroIndex]);

            EditMacroScreen screen(mSurface,
                                   mEventManager,
                                   macro);

            screen.redraw();

            mEventManager.poll(
                [&](const KeyEvent& event,
                    KeyEventStage&  next)
                {
                    return screen.processKeyEvent(event, next);
                });
        }
    }
    
    return false;
}
