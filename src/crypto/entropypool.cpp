#include "crypto/entropypool.h"

#include <mbedtls/sha256.h>

std::array<uint8_t, 32> EntropyPool::read()
{
    std::array<uint8_t, 32> val;

    val.fill(0x0);
    
    // mCount = std::min(mCount, mData.size());
    
    // if (mCount >= val.size())
    // {
    //     mCount -= val.size();    
    // }
    
    // mbedtls_sha256(mData.begin() + mCount, val.size(), val.begin(), 0);
    
    return val;
}

std::array<uint8_t, 16> EntropyPool::read128()
{
    std::array<uint8_t, 16> val;

    val.fill(0x0);
    
    // mCount = std::min(mCount, mData.size());
    
    // if (mCount >= val.size())
    // {
    //     mCount -= val.size();    
    // }
    
    // mbedtls_sha256(mData.begin() + mCount, val.size(), val.begin(), 0);
    
    return val;
}
