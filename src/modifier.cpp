#include "modifier.h"

Modifier::Modifier()
    : mRefCount(0)
{ }

bool Modifier::active() const
{
    return (mRefCount != 0);
}

bool Modifier::pressed()
{
    mRefCount = 1;

    return true;
}

bool Modifier::released()
{
    mRefCount = 0;

    return true;
}
