#include "actionprocessor.h"

#include "hardware/ctrlutil.h"
#include "event/event.h"
#include "event/actionevent.h"

ActionProcessor::ActionProcessor(EventStage& next)
    : mNext(next)
{ }

bool ActionProcessor::processEvent(const Event& event)
{
    if (event.is<ActionEvent>())
    {
        auto actionId(event.get<ActionEvent>().actionId);
        
        switch (actionId)
        {
        case 0:
            CtrlUtil::bootloader();
            break;
            
        default:
            break;
        }
    }
    else
    {
        mNext.processEvent(event);
    }

    return true;
}

