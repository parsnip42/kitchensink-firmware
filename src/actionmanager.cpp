#include "actionmanager.h"

ActionManager::ActionManager()
{ }

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
