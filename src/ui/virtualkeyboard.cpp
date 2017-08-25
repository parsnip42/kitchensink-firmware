#include "ui/virtualkeyboard.h"

#include "event/event.h"
#include "event/keyevent.h"
#include "data/keymap.h"

VirtualKeyboard::VirtualKeyboard()
    : mActiveChar('\0')
{ }

bool VirtualKeyboard::processEvent(const Event& event)
{
    if (!mModifierState.processEvent(event))
    {
        if (event.is<KeyEvent>())
        {
            auto keyEvent(event.get<KeyEvent>());

            if (keyEvent.pressed)
            {
                if (mModifierState.shift())
                {
                    mActiveChar = KeyMap::getEntry(keyEvent.keyCode).shift;
                }
                else
                {
                    mActiveChar = KeyMap::getEntry(keyEvent.keyCode).dflt; 
                }
            }
        }
    }

    return true;
}

char VirtualKeyboard::consumeChar()
{
    auto consumed(mActiveChar);

    mActiveChar = '\0';
    
    return consumed;
}

