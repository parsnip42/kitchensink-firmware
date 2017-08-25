#ifndef INCLUDED_VIRTUALKEYBOARD_H
#define INCLUDED_VIRTUALKEYBOARD_H

#include "event/eventstage.h"
#include "modifierstate.h"

class VirtualKeyboard : public EventStage
{
public:
    VirtualKeyboard();

public:
    virtual bool processEvent(const Event& keyEvent) override;
    char consumeChar();
    
private:
    ModifierState mModifierState;
    char          mActiveChar;
};

#endif






