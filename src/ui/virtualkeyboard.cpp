#include "ui/virtualkeyboard.h"

#include "keyevent.h"
#include "data/keymap.h"

VirtualKeyboard::VirtualKeyboard()
    : mActiveChar('\0')
{ }

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
                    mActiveChar = KeyMap::getEntry(keyId.value()).shift;
                }
                else
                {
                    mActiveChar = KeyMap::getEntry(keyId.value()).dflt; 
                }
            }
        }
    }
}

char VirtualKeyboard::consumeChar()
{
    auto consumed(mActiveChar);

    mActiveChar = '\0';
    
    return consumed;
}

