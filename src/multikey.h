#ifndef INCLUDED_MULTIKEY_H
#define INCLUDED_MULTIKEY_H

#include "keyid.h"
#include "types/strbuf.h"
#include "config.h"

#include <array>

class KeyEvent;
class KeyEventStage;

class MultiKey
{
public:
    typedef std::array<KeyId, Config::kMultiKeyKeyCount> Keys;
    
public:
    MultiKey();
    
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
MultiKey::MultiKey()
    : mTaps(0)
    , mReleased(false)
    , mTriggered(false)
{ }

inline
KeyId MultiKey::key(int taps)
{
    std::size_t index(taps - 1);
    
    if (index < keys.size())
    {
        return keys[index];
    }

    return KeyId();
}

#endif
