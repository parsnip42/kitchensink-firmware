#include "actionprocessor.h"

#include "eventqueue.h"

bool ActionProcessor::processEvent(const KeyEvent& event,
                                   EventQueue&     eventQueue)
{
    if (event.keyId.type() == KeyId::Type::kAction)
    {
        fireAction(event.keyId.value(),
                   event,
                   eventQueue);
        
        return true;
    }

    return false;
}

void ActionProcessor::fireAction(int             action,
                                 const KeyEvent& event,
                                 EventQueue&     eventQueue) const
{
    if (action >= 0 && action < kMaxActions)
    {
        const auto& func(mActions[action]);

        if (func)
        {
            func(event, eventQueue);
        }
    }
}

void ActionProcessor::registerAction(int         action,
                                     const Func& func)
{
    if (action >= 0 && action < kMaxActions)
    {
        mActions[action] = func;
    }
}
