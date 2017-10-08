#include "debounce.h"

bool Debounce::process(uint32_t       timeMs,
                       const KeyMask& next)
{
    mCurrent &= next;
    
    if (timeMs >= (mLastMs + kLatencyMs))
    {
        mDelta = mState;
        mDelta ^= mCurrent;
        mState = mCurrent;
        
        mCurrent = next;
        mLastMs = timeMs;
        
        return !mDelta.empty();
    }
    
    return false;
}

