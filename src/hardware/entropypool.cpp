#include "hardware/entropypool.h"

#include <mbedtls/sha256.h>

std::array<uint8_t, 32> EntropyPool::read()
{
    std::array<uint8_t, 32> val;

    mbedtls_sha256(mData.begin(), mData.size(), val.begin(), 0);
    
    return val;
}
