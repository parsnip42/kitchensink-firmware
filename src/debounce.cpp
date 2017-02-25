#include "debounce.h"

bool Debounce::process(const KeyMask& next)
{
    mCounter = (mCounter + 1) % (kLatency + 1);
    
    if (mCounter == 0)
    {
        mDelta = mState;
        mDelta ^= mCurrent;
        mState = mCurrent;
        mCurrent = next;
    }
    else
    {
        mCurrent |= next;
    }
    
    return (mCounter == 0 && !mDelta.empty());
}
