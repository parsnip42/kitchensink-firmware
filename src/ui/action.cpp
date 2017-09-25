#include "ui/action.h"

namespace
{

auto nullFunc([](void*) -> bool
{
    return false;
});

}

Action Action::trigger(bool& value)
{
    return Action(&value, [](void* data) -> bool
    {
        (*reinterpret_cast<bool*>(data)) = true;
        
        return true;
    });
}

Action::Action()
    : mData(nullptr)
    , mFunc(nullFunc)
{ }

Action::Action(void*       data,
               const Func& func)
    : mData(data)
    , mFunc(func)
{ }

bool Action::fireAction()
{
    return mFunc(mData);
}
