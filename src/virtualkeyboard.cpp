#include "virtualkeyboard.h"

#include "data/keymap.h"

void VirtualKeyboard::processKeyEvent(const KeyEvent& keyEvent)
{
    if (!mModifierState.processEvent(keyEvent))
    {
        mAutoRepeat.processKeyEvent(keyEvent);
    }
}

VirtualKeyboard::State VirtualKeyboard::readState()
{
    State state;

    auto activeKey(mAutoRepeat.activeKey());

    state.activeKey = activeKey;

    if (mModifierState.shift())
    {
        state.activeChar = KeyMap::getEntry(activeKey.value()).shift;
    }
    else
    {
        state.activeChar = KeyMap::getEntry(activeKey.value()).dflt; 
    }

    return state;
}
