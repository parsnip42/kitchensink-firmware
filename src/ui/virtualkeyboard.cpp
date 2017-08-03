#include "ui/virtualkeyboard.h"

#include "keyevent.h"
#include "data/keymap.h"

VirtualKeyboard::VirtualKeyboard()
{
    state.activeKey = KeyId();
    state.activeChar = '\0';
}

void VirtualKeyboard::processKeyEvent(const KeyEvent& event)
{
    if (!mModifierState.processEvent(event))
    {
        auto keyId(event.keyId);

        if (keyId.type() == KeyId::Type::kKey)
        {
            if (event.pressed)
            {
                if (mModifierState.shift())
                {
                    state.activeChar = KeyMap::getEntry(keyId.value()).shift;
                }
                else
                {
                    state.activeChar = KeyMap::getEntry(keyId.value()).dflt; 
                }
            }
            else if (keyId == state.activeKey && !event.pressed)
            {
                state.activeChar = '\0';
            }
        }

        state.activeKey = keyId;
    }
}
