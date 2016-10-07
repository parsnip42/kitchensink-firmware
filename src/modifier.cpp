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
    ++mRefCount;

    return true;
}

bool Modifier::released()
{
    --mRefCount;

    return true;
}
