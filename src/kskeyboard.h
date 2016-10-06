#ifndef INCLUDED_KSKEYBOARD_H
#define INCLUDED_KSKEYBOARD_H

#include "keymatrixevent.h"
#include "keyboardplate.h"
#include "layerstack.h"
#include "tapping.h"

class KsKeyboard
{
public:
    typedef KeyMatrixEvent Event;
    
public:
    KsKeyboard();

public:
    template <typename Callback>
    bool poll(const Callback& callback); 

private:
    bool scan();
    
private:
    KeyboardPlate mLeft;
    KeyboardPlate mRight;

private:
    KsKeyboard(const KsKeyboard&) = delete;
    KsKeyboard& operator=(const KsKeyboard&) = delete;
};


template <typename Callback>
inline
bool KsKeyboard::poll(const Callback& callback)
{
    bool hasEvent(scan());

    if (hasEvent)
    {
        mLeft.dispatch(callback);
        mRight.dispatch(callback);
    }

    return hasEvent;
}

#endif
