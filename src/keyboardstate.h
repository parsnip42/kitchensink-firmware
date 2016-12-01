#ifndef INCLUDED_KEYBOARDSTATE_H
#define INCLUDED_KEYBOARDSTATE_H

#include "layerstack.h"
#include "macroset.h"
#include "modifierset.h"

class KeyboardState
{
public:
    constexpr KeyboardState() = default;

public:
    LayerStack  layerStack;
    MacroSet    macroSet;
    ModifierSet modifierSet;
    
private:
    KeyboardState(const KeyboardState&);
    KeyboardState& operator=(const KeyboardState&);    
};

#endif
