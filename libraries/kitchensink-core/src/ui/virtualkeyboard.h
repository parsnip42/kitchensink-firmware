#ifndef INCLUDED_VIRTUALKEYBOARD_H
#define INCLUDED_VIRTUALKEYBOARD_H

#include "event/eventstage.h"
#include "modifierstate.h"

class VirtualKeyboard
{
public:
    VirtualKeyboard();

public:
    bool processEvent(const Event& keyEvent);
    char consumeChar();
    
private:
    ModifierState mModifierState;
    char          mActiveChar;
};

#endif






