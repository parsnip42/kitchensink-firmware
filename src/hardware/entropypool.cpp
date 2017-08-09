#include "hardware/entropypool.h"

void EntropyPool::insert(uint8_t value)
{
    mData[mCount % mData.size()] = value;

    ++mCount;
}










