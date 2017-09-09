#include "keyboardstate.h"

void KeyboardState::reset()
{
    layerStack.reset();
    macroSet.reset();
    secureMacroSet.reset();
    multiKeySet = MultiKeySet();
    smartKeySet = SmartKeySet();
}
