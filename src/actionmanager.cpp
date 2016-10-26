#include "actionmanager.h"

#include "actioncontext.h"

ActionManager::ActionManager()
{ }

bool ActionManager::processEvent(const KeyEvent& event, EventQueue&)
{
    if (event.keyId.type() == KeyId::kAction)
    {
        fireAction(event.keyId.value(),
                   ActionContext(event.pressed,
                                 event.taps));
        
        return true;
    }

    return false;
}

void ActionManager::fireAction(int action, const ActionContext& context) const
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

void ActionManager::registerAction(int action, const Func& func)
{
    if (action >= 0 && action < kMaxActions)
    {
        mActions[action] = func;
    }
}
