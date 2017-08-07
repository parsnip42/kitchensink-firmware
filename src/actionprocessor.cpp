#include "actionprocessor.h"

#include "ctrlutil.h"
#include "keyevent.h"

ActionProcessor::ActionProcessor(KeyEventStage& next)
    : mNext(next)
{ }

void ActionProcessor::processKeyEvent(const KeyEvent& event)
{
    const auto& keyId(event.keyId);
    
    if (keyId.type() == KeyId::Type::kAction)
    {
        if (event.pressed)
        {
            switch (keyId.value())
            {
            case 0:
                CtrlUtil::bootloader();
                break;
                
            default:
                break;
            }
        }
    }

    mNext.processKeyEvent(event);
}

