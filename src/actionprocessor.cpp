#include "actionprocessor.h"

#include "hardware/ctrlutil.h"
#include "event/event.h"

ActionProcessor::ActionProcessor(EventStage& next)
    : mNext(next)
{ }

void ActionProcessor::processEvent(const Event& event)
{
    // const auto& keyId(event.keyId);
    
    // if (keyId.type() == KeyId::Type::kAction)
    // {
    //     if (event.pressed)
    //     {
    //         switch (keyId.value())
    //         {
    //         case 0:
    //             CtrlUtil::bootloader();
    //             break;
                
    //         default:
    //             break;
    //         }
    //     }
    // }

    mNext.processEvent(event);
}

