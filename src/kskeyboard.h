#ifndef INCLUDED_KSKEYBOARD_H
#define INCLUDED_KSKEYBOARD_H

#include "eventdispatcher.h"
#include "keyboardplate.h"
#include "keymatrixevent.h"

class KsKeyboard
{
public:
    typedef EventDispatcher::Callback Callback;
    typedef KeyMatrixEvent            Event;
    
public:
    KsKeyboard();

public:
    bool poll(const Callback& callback); 
    
private:
    KeyboardPlate mLeft;
    KeyboardPlate mRight;
    
private:
    KsKeyboard(const KsKeyboard&);
    KsKeyboard& operator=(const KsKeyboard&);
};

#endif
