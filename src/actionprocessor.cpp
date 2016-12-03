#include "actionprocessor.h"
#include "ctrlutil.h"
#include "eventqueue.h"
#include "menudefinitions.h"

ActionProcessor::ActionProcessor(KeyProcessor&  keyProcessor,
                                 KeyboardState& keyboardState,
                                 UI::Surface&   surface)
    : mKeyProcessor(keyProcessor)
    , mKeyboardState(keyboardState)
    , mSurface(surface)
    , mMenuDefinitions(keyboardState)
{ }

bool ActionProcessor::processEvent(const KeyEvent& event)
{
    const auto& keyId(event.keyId);
    
    if (event.pressed && (keyId.type() == KeyId::Type::kAction))
    {
        switch (keyId.actionType())
        {
        case KeyId::ActionType::kBuiltIn:
            fireBuiltIn(event.keyId.value(),
                        event);

        case KeyId::ActionType::kMenu:
            fireMenu(event.keyId.value(),
                     event);
        }
        
        return true;
    }

    return false;
}

void ActionProcessor::fireBuiltIn(int             action,
                                  const KeyEvent& event) const
{
    CtrlUtil::bootloader();
}

void ActionProcessor::fireMenu(int             action,
                               const KeyEvent& event) const
{
    UI::Menu menu(mSurface);

    menu.createMenu(mMenuDefinitions.getDataSource(action),
                    mKeyProcessor);
}

