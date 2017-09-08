#include "modifierstate.h"

#include "event/event.h"
#include "event/keyevent.h"

bool ModifierState::processEvent(const Event& event)
{
    if (event.is<KeyEvent>())
    {
        auto keyEvent(event.get<KeyEvent>());
        auto keyCode(static_cast<uint8_t>(keyEvent.key));

        if (keyCode >= KeyCodes::ModifierOffset)
        {
            std::size_t modifier(keyCode - KeyCodes::ModifierOffset);

            if (modifier < keyState.size())
            {
                keyState[modifier] = keyEvent.pressed;
            }
            
            return true;
        }
    }

    return false;
}
