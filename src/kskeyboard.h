#ifndef INCLUDED_KSKEYBOARD_H
#define INCLUDED_KSKEYBOARD_H

#include "keymatrixevent.h"
#include "keyboardplate.h"
#include "layerstack.h"
#include "tapping.h"

class KsKeyboard
{
public:
    class Event
    {
    public:
        Event(KeyId           nKeyId,
              KeyState::Value nState,
              int             nTaps);
        
    public:
        KeyId           keyId;
        KeyState::Value state;
        int             taps;
    };
    
public:
    KsKeyboard();

public:
    template <typename Callback>
    bool poll(const Callback& callback); 

    void assignLayer(const Layer* layer, int index);
    void setLayer(int index, bool enabled);
    bool enabled(int layer) const;

private:
    bool scan();
    Event processKeyMatrixEvent(const KeyMatrixEvent& event);
    
private:
    KeyboardPlate mLeft;
    KeyboardPlate mRight;
    LayerStack    mLayerStack;
    Tapping       mTapping;

private:
    KsKeyboard(const KsKeyboard&) = delete;
    KsKeyboard& operator=(const KsKeyboard&) = delete;
};


inline
KsKeyboard::Event::Event(KeyId           nKeyId,
                         KeyState::Value nState,
                         int             nTaps)
    : keyId(nKeyId)
    , state(nState)
    , taps(nTaps)
{ }

template <typename Callback>
inline
bool KsKeyboard::poll(const Callback& callback)
{
    bool hasEvent(scan());

    if (hasEvent)
    {
        auto plateCallback([&](const KeyMatrixEvent& event)
        {
            callback(processKeyMatrixEvent(event));
        });

        mLeft.dispatch(plateCallback);
        mRight.dispatch(plateCallback);
    }

    return hasEvent;
}

#endif
