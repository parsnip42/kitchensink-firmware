#include "tapping.h"

#include <elapsedMillis.h>

Tapping::Tapping(uint32_t tapDelay)
    : mTapDelay(tapDelay)
    , mKeyId(KeyId::None)
    , mCount(1)
    , mLastTap(0)
{ }

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
