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
            std::size_t modifier(keyCode - KeyCodes::ModifierOffset);

            if (modifier < keyState.size())
            {
                keyState[modifier] = event.pressed;
            }
            
            return true;
        }
    }

    return false;
}
