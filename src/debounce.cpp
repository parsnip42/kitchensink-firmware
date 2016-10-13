#include "debounce.h"

Debounce::Debounce(unsigned int latency)
    : mLatency(latency + 1)
    , mCounter(0)
{ }

bool Debounce::process(const KeyMask& next)
{
    mCounter = (mCounter + 1) % mLatency;
    
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
    }
    
    return (mCounter == 0 && !mDelta.empty());
}

