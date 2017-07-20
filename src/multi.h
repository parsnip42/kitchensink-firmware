#ifndef INCLUDED_MULTI_H
#define INCLUDED_MULTI_H

#include "keyid.h"
#include "types/strbuf.h"

#include <array>

class EventQueue;
class KeyEvent;

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
    void release(EventQueue& eventQueue);
    bool trigger(EventQueue& eventQueue);
    bool trigger(const KeyEvent& triggerEvent,
                 EventQueue&     eventQueue);

public:
    StrBuf<12>           title;
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
