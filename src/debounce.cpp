#include "debounce.h"

Debounce::Debounce(unsigned int latency)
    : mLatency(latency + 1)
    , mCounter(0)
{ }

bool Debounce::process(const KeyMatrix::Mask& next)
{
    if (mCounter == 0)
    {
        mDelta = mState;
        mDelta ^= mCurrent;
        mState = mCurrent;
        mCurrent = next;
    }
    else
    {
        mCurrent &= next;
        mDelta = KeyMatrix::Mask();
    }
    
    mCounter = (mCounter + 1) % mLatency;

    return (!mState.empty() || !mDelta.empty());
}

