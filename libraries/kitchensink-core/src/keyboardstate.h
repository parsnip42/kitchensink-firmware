#ifndef INCLUDED_KEYBOARDSTATE_H
#define INCLUDED_KEYBOARDSTATE_H

#include "globalconfig.h"
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
    GlobalConfig   globalConfig;
    LayerStack     layerStack;
    MacroSet       macroSet;
    SecureMacroSet secureMacroSet;
    MultiKeySet    multiKeySet;
    SmartKeySet    smartKeySet;
    
private:
    KeyboardState(const KeyboardState&) = delete;
    KeyboardState& operator=(const KeyboardState&) = delete;
};

#endif
