#ifndef INCLUDED_TAPPING_H
#define INCLUDED_TAPPING_H

#include "keyid.h"

#include <cstdint>

class Tapping
{
public:
    explicit Tapping(uint32_t tapDelay);

public:
    void processKey(const KeyId& keyId);
    
public:
    uint8_t count(const KeyId& keyId);
    
private:
    uint32_t mTapDelay;
    KeyId    mKeyId;
    uint32_t mLastTap;
    uint8_t  mCount;
};


inline
uint8_t Tapping::count(const KeyId& keyId)
{
    if (keyId == mKeyId)
    {
        return mCount;
    }
    else
    {
        return 0;
    }
}

#endif
