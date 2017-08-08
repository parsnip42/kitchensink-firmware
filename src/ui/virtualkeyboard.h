#ifndef INCLUDED_VIRTUALKEYBOARD_H
#define INCLUDED_VIRTUALKEYBOARD_H

#include "keyid.h"
#include "keyeventstage.h"
#include "modifierstate.h"

class VirtualKeyboard : public KeyEventStage
{
public:
    VirtualKeyboard();

public:
    virtual void processKeyEvent(const KeyEvent& keyEvent) override;
    char consumeChar();
    
private:
    ModifierState mModifierState;
    char          mActiveChar;
};

#endif






