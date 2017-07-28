#ifndef INCLUDED_MULTI_H
#define INCLUDED_MULTI_H

#include "keyid.h"
#include "types/strbuf.h"
#include "config.h"

#include <array>

class KeyEvent;
class KeyEventStage;

class Multi
{
public:
    typedef std::array<KeyId, Config::kMultiKeyKeyCount> Keys;
    
public:
    Multi();
    
public:
    KeyId key(int taps);

    void press();
    void release(KeyEventStage& next);
    bool trigger(KeyEventStage& next);

public:
    StrBuf<Config::kMultiKeyNameLen> name;
    Keys                             keys;

private:
    uint8_t mTaps;
    KeyId   mActiveKey;
    bool    mReleased;
    bool    mTriggered;
};


inline
Multi::Multi()
    : mTaps(0)
    , mReleased(false)
    , mTriggered(false)
{ }

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

#endif
