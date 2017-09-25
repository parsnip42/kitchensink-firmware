#include "crypto/entropypool.h"

#include "crypto/cryptoutil.h"

#include <mbedtls/sha256.h>

bool EntropyPool::read(std::array<uint8_t, 32>& output)
{
    // Clip pool back to max size if it's overflowed.
    mCount = std::min(mCount, mData.size());

    // Amount of source data to use from the pool relative to the size of the
    // ouput hash.
    auto sourceSize(output.size() * Config::kEntropySourceFactor);

    // Not enough data in pool.
    if (mCount < sourceSize)
    {
        return false;
    }

    mCount -= sourceSize;

    output = CryptoUtil::sha256(mData.begin() + mCount,
                                mData.begin() + mCount + sourceSize);    
    
    return true;
}
