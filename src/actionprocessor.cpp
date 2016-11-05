#include "actionprocessor.h"

#include "actioncontext.h"

bool ActionProcessor::processEvent(const KeyEvent& event, EventQueue&)
{
    if (event.keyId.type() == KeyId::Type::kAction)
    {
        fireAction(event.keyId.value(),
                   ActionContext(event.pressed,
                                 event.taps));
        
        return true;
    }

    return false;
}

void ActionProcessor::fireAction(int action, const ActionContext& context) const
{
    if (action >= 0 && action < kMaxActions)
    {
        const auto& func(mActions[action]);

        if (func)
        {
            func(context);
        }
    }
}

void ActionProcessor::registerAction(int action, const Func& func)
{
    if (action >= 0 && action < kMaxActions)
    {
        mActions[action] = func;
    }
}
