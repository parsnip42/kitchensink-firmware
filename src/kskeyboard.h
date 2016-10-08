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
    void poll(const Callback& callback); 

    template <typename Callback>
    void pressed(const Callback& callback); 

private:
    KeyboardPlate mLeft;
    KeyboardPlate mRight;

private:
    KsKeyboard(const KsKeyboard&) = delete;
    KsKeyboard& operator=(const KsKeyboard&) = delete;
};


template <typename Callback>
inline
void KsKeyboard::poll(const Callback& callback)
{
    mLeft.poll(callback);
    mRight.poll(callback);
}

template <typename Callback>
inline
void KsKeyboard::pressed(const Callback& callback)
{
    mLeft.pressed(callback);
    mRight.pressed(callback);
}

#endif
