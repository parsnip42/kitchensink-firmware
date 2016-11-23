#include "tapping.h"

#include <elapsedMillis.h>

void Tapping::processKey(const KeyId& keyId)
{
    auto tapTime(millis());
    
    if (keyId == mKeyId)
    {
        if ((tapTime - mLastTap) <= mTapDelay)
        {
            ++mCount;
        }
        else
        {
            mCount = 1;
        }
    }
    else
    {
        mKeyId = keyId;
        mCount = 1;
    }
    
    mLastTap = tapTime;
}
