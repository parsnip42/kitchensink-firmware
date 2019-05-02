#include "ui/virtualkeyboard.h"

#include "event/event.h"
#include "event/keyevent.h"
#include "data/keymap.h"

VirtualKeyboard::VirtualKeyboard()
    : mActiveChar('\0')
{ }

bool VirtualKeyboard::processEvent(const Event& event)
{
    if (mModifierState.processEvent(event))
    {
        return true;
    }

    if (event.is<KeyEvent>())
    {
        auto keyEvent(event.get<KeyEvent>());
        
        char nextChar;
        
        if (mModifierState.shift())
        {
            nextChar = KeyMap::getEntry(keyEvent.key).shift;
        }
        else
        {
            nextChar = KeyMap::getEntry(keyEvent.key).dflt;
        }
        
        if (keyEvent.pressed)
        {
            mActiveChar = nextChar;
        }
        
        return (nextChar != 0);
    }

    return false;
}

char VirtualKeyboard::consumeChar()
{
    auto consumed(mActiveChar);

    mActiveChar = '\0';
    
    return consumed;
}

