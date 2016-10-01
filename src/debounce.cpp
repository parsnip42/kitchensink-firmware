#include "debounce.h"

Debounce::Debounce(int latency)
    : mLatency(latency)
    , mFiltered(0)
{
    mStableCount.fill(0);
}

bool Debounce::process(const KeyMatrix::Mask& next)
{
    bool delta(false);
    
    for (int row(0); row < KeyMatrix::kRows; ++row)
    {
        if (next[row] != mLast[row])
        {
            if (mStableCount[row] > 0)
            {
                ++mFiltered;
            }
            
            mStableCount[row] = 1;
            mLast[row] = next[row];
        }
        else if (mStableCount[row] > 0)
        {
            ++mStableCount[row];
            
            if (mStableCount[row] > mLatency)
            {
                mDelta[row] = mState[row];
                mDelta[row] ^= next[row];
                mState[row] = next[row];

                delta = true;
                mStableCount[row] = 0;
            }
        }
    }

    return delta;
}
