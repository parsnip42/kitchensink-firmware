#include "debounce.h"

Debounce::Debounce(int latency)
    : mLatency(latency)
{
    mStableCount.fill(0);
}

bool Debounce::scan(KeyMatrix& keyMatrix)
{
    bool delta(false);
    
    for (int row(0); row < KeyMatrix::kRows; ++row)
    {
        if (keyMatrix.delta()[row].empty()
            && mStableCount[row] > 0)
        {
            ++mStableCount[row];
            
            if (mStableCount[row] > mLatency)
            {
                mDelta[row] = mState[row];
                mDelta[row] ^= keyMatrix.state()[row];
                mState[row] = keyMatrix.state()[row];

                delta = true;
                mStableCount[row] = 0;
            }
        }
        else
        {
            mStableCount[row] = 1;
        }
    }

    return delta;
}
