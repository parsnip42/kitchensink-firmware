#ifndef INCLUDED_VIRTUALKEYBOARD_H
#define INCLUDED_VIRTUALKEYBOARD_H

#include "keyeventstage.h"
#include "autorepeat.h"
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
    VirtualKeyboard() = default;

public:
    virtual void processKeyEvent(const KeyEvent& keyEvent) override;

public:
    State readState();
    
private:
    AutoRepeat    mAutoRepeat;
    ModifierState mModifierState;

};

#endif /* INCLUDED_VIRTUALKEYBOARD_H */






