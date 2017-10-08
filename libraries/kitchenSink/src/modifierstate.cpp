#include "modifierstate.h"

#include "event/event.h"
#include "event/keyevent.h"

bool ModifierState::processEvent(const Event& event)
{
    if (event.is<KeyEvent>())
    {
        auto keyEvent(event.get<KeyEvent>());
        auto key(keyEvent.key);

        if (KeyCodeUtil::modifier(key))
        {
            keyState[KeyCodeUtil::modifierIndex(key)] = keyEvent.pressed;
            
            return true;
        }
    }

    return false;
}
