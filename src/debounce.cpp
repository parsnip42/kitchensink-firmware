#include "debounce.h"

Debounce::Debounce(int latency)
    : mLatency(latency)
    , mFiltered(0)
{
    mStableCount.fill(0);
}

bool Debounce::process(const KeyMatrix::Mask& next)
{
    bool populated(false);
    
    for (int row(0); row < KeyMatrix::kRows; ++row)
    {
        mDelta[row] = KeyMatrix::Mask::Row();
        
        if (next[row] != mLast[row])
        {
            mStableCount[row] = 0;
        }
        else if (++mStableCount[row] > mLatency)
        {
            mDelta[row] = mState[row];
            mDelta[row] ^= next[row];
            mState[row] = next[row];
            
            mStableCount[row] = 0;
        }

        mLast[row] = next[row];

        if (mDelta[row].data() || mState[row].data())
        {
            populated = true;
        }
    }

    return populated;
}

