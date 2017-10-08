#include "crypto/entropypool.h"

#include "crypto/cryptoutil.h"

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

    // Hash from the beginning of the entropy pool - this is the most likely to
    // be composed of multiple entries of random data.
    output = CryptoUtil::sha256(mData.begin(),
                                mData.begin() + sourceSize);

    // Move the following block of data to the beginning of the entropy pool
    // (it's perfectly fine to leave the trailing remaining data as is).
    std::move(mData.begin() + sourceSize, 
              mData.begin() + mCount,
              mData.begin());

    // And finally reduce the size of the pool to match.
    mCount -= sourceSize;
    
    return true;
}
