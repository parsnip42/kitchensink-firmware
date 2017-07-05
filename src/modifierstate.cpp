#include "modifierstate.h"

#include "keyevent.h"

bool ModifierState::processEvent(const KeyEvent& event)
{
    auto keyId(event.keyId);
    
    if (keyId.type() == KeyId::Type::kKey)
    {
        auto keyCode(keyId.value());

        if (keyCode >= KeyCodes::ModifierOffset)
        {
            auto modifier(keyCode - KeyCodes::ModifierOffset);
            
            keyState[modifier] = event.pressed;
            
            return true;
        }
    }

    return false;
}
