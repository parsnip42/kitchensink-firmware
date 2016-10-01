#ifndef INCLUDED_TAPPING_H
#define INCLUDED_TAPPING_H

#include "keyid.h"

#include <cstdint>

class Tapping
{
public:
    explicit Tapping(uint32_t tapDelay);

public:
    void processKey(KeyId keyId);
    
public:
    int count(const KeyId& keyId);
    
private:
    const uint32_t mTapDelay;
    KeyId          mKeyId;
    int            mCount;
    uint32_t       mLastTap;
};


inline
int Tapping::count(const KeyId& keyId)
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
