#include "debounce.h"

Debounce::Debounce(int latency)
    : mLatency(latency)
    , mCounter(0)
{ }

bool Debounce::process(const KeyMatrix::Mask& next)
{
    if (mCounter == 0)
    {
        mCurrent = next;
    }
    else
    {
        mCurrent &= next;
    }

    if (mCounter++ >= mLatency)
    {
        mDelta = mState;
        mDelta ^= mCurrent;
        mState = mCurrent;

        mCounter = 0;
    }
    else
    {
        mDelta = KeyMatrix::Mask();
    }

    return !mDelta.empty() || !mState.empty();
}

