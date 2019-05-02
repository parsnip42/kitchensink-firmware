#include "keyboardstate.h"

void KeyboardState::reset()
{
    layerStack.clear();
    macroSet.clear();
    secureMacroSet.clear();
    multiKeySet = MultiKeySet();
    smartKeySet = SmartKeySet();
}
