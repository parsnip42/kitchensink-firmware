#ifndef INCLUDED_MULTI_H
#define INCLUDED_MULTI_H

#include "keyid.h"
#include "types/strbuf.h"

#include <array>

class KeyEvent;
class KeyEventStage;

class Multi
{
public:
    Multi()
        : mTaps(0)
        , mReleased(false)
        , mTriggered(false)
    {

    }
    
public:
    KeyId key(int taps);

    void press();
    void release(KeyEventStage& next);
    bool trigger(KeyEventStage& next);

public:
    StrBuf<12>           name;
    std::array<KeyId, 5> keys;

private:
    uint8_t mTaps;
    KeyId   mActiveKey;
    bool    mReleased;
    bool    mTriggered;
};

inline
KeyId Multi::key(int taps)
{
    std::size_t index(taps - 1);
    
    if (index < keys.size())
    {
        return keys[index];
    }

    return KeyId();
}

#endif /* INCLUDED_MULTI_H */
