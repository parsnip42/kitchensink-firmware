#ifndef INCLUDED_MODIFIER_H
#define INCLUDED_MODIFIER_H

#include "keyevent.h"

#include <cstdint>

class Modifier
{
public:
    Modifier();

public:
    bool processEvent(const KeyEvent& keyEvent);
    
private:
    bool mState;
    bool mSingleTrigger;
};

#endif
