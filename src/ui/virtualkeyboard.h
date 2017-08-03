#ifndef INCLUDED_VIRTUALKEYBOARD_H
#define INCLUDED_VIRTUALKEYBOARD_H

#include "keyid.h"
#include "keyeventstage.h"
#include "modifierstate.h"

class VirtualKeyboard : public KeyEventStage
{
public:
    class State
    {
    public:
        KeyId activeKey;
        char  activeChar;
    };
        
public:
    VirtualKeyboard();

public:
    virtual void processKeyEvent(const KeyEvent& keyEvent) override;

public:
    State state;
    
private:
    ModifierState mModifierState;

};

#endif /* INCLUDED_VIRTUALKEYBOARD_H */






