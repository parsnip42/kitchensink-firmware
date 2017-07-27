#include "ui/screenstack.h"

#include "keyboardstate.h"
#include "menudefinitions.h"
#include "ui/menu.h"

#include "ui/editmacroscreen.h"

void ScreenStack::processKeyEvent(const KeyEvent& event)
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
            
            mSurface.clear();
        }

    }
    else if (keyId.actionType() == KeyId::ActionType::kEditMacro)
    {
        if (event.pressed)
        {
            auto macroIndex(keyId.value());
            auto& macro(mKeyboardState.macroSet[macroIndex]);

            EditMacroScreen screen(mSurface,
                                   mEventManager,
                                   mKeyboardState.macroSet,
                                   macro);

            screen.poll();
        }
    }
    else
    {
        mNext.processKeyEvent(event);
    }
}
