#ifndef INCLUDED_KEYBOARDSTATE_H
#define INCLUDED_KEYBOARDSTATE_H

#include "layerstack.h"
#include "macroset.h"
#include "multikeyset.h"
#include "smartkeyset.h"

class KeyboardState
{
public:
    KeyboardState() = default;

public:
    void reset();
    
public:
    LayerStack  layerStack;
    MacroSet    macroSet;
    MacroSet    secureMacroSet;
    MultiKeySet multiKeySet;
    SmartKeySet smartKeySet;
    
private:
    KeyboardState(const KeyboardState&) = delete;
    KeyboardState& operator=(const KeyboardState&) = delete;
};

#endif
