#include "ui/screenstack.h"

#include "keyboardstate.h"
#include "menudefinitions.h"
#include "ui/menuscreen.h"
#include "ui/editmacroscreen.h"
#include "ui/storagescreen.h"
#include "ui/benchmarkscreen.h"

#include "types/arrayobjectsource.h"

void ScreenStack::processKeyEvent(const KeyEvent& event)
{
    auto keyId(event.keyId);

    if (keyId.type() == KeyId::Type::kAction)
    {
        if (event.pressed)
        {
            processKeyId(keyId);
        }
    }
    else
    {
        mNext.processKeyEvent(event);
    }
}

void ScreenStack::processKeyId(const KeyId& keyId)
{
    if (keyId.actionType() == KeyId::ActionType::kMenu)
    {
        MenuDefinitions menuDefinitions(mKeyboardState);

        auto action(keyId.value());
            
        MenuScreen menu(menuDefinitions.getTitle(action),
                        menuDefinitions.getDataSource(action),
                        mSurface,
                        mEventManager);

        menu.poll();

    }
    else if (keyId.actionType() == KeyId::ActionType::kScreen)
    {
        switch (keyId.value())
        {
        case 0:
        {
            StorageScreen storage(mSurface,
                                  mEventManager);

            storage.poll();
            break;
        }

        case 1:
        {
            BenchmarkScreen benchmark(mSurface,
                                      mEventManager);

            benchmark.poll();
            break;
        }

        default:
            break;
        }
    }
    else if (keyId.actionType() == KeyId::ActionType::kEditMacro)
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
