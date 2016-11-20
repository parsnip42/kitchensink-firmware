#include "actionprocessor.h"
#include "ctrlutil.h"
#include "eventqueue.h"
#include "menudefinitions.h"


ActionProcessor::ActionProcessor(KeyHandler&  keyHandler,
                                 UI::Surface& surface)
    : mKeyHandler(keyHandler)
    , mSurface(surface)
{ }

bool ActionProcessor::processEvent(const KeyEvent& event,
                                   EventQueue&     eventQueue)
{
    const auto& keyId(event.keyId);
    
    if (keyId.type() == KeyId::Type::kAction)
    {
        switch (keyId.actionType())
        {
        case KeyId::ActionType::kBuiltIn:
            fireBuiltIn(event.keyId.value(),
                        event,
                        eventQueue);

        case KeyId::ActionType::kMenu:
            fireMenu(event.keyId.value(),
                     event,
                     eventQueue);
        }
        
        return true;
    }

    return false;
}

void ActionProcessor::fireBuiltIn(int             action,
                                  const KeyEvent& event,
                                  EventQueue&     eventQueue) const
{
    CtrlUtil::bootloader();
}

void ActionProcessor::fireMenu(int             action,
                               const KeyEvent& event,
                               EventQueue&     eventQueue) const
{
    UI::Menu menu(mSurface);

    menu.createMenu(MenuDefinitions::getDataSource(action),
                    mKeyHandler,
                    eventQueue);
}

