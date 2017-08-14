#include "modifierstate.h"

#include "event/event.h"
#include "event/keyevent.h"

bool ModifierState::processEvent(const Event& event)
{
    if (event.is<KeyEvent>())
    {
        auto keyEvent(event.get<KeyEvent>());
        auto keyCode(keyEvent.keyCode);

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
