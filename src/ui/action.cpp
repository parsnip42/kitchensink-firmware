#include "ui/action.h"

namespace
{

auto nullFunc([](void*) -> bool
{
    return false;
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
