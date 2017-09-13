#include "hardware/entropypool.h"

#include <mbedtls/sha256.h>

std::array<uint8_t, 32> EntropyPool::read()
{
    std::array<uint8_t, 32> val;

    val.fill(0);
    
    mCount = std::min(mCount, mData.size());
    
    if (mCount >= val.size())
    {
        mCount -= val.size();
        
        mbedtls_sha256(mData.begin() + mCount, val.size(), val.begin(), 0);
        // std::copy(mData.begin() + mCount, mData.begin() + mCount + val.size(), val.begin());
    }
    
    return val;
}
