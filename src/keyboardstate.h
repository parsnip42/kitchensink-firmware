#ifndef INCLUDED_KEYBOARDSTATE_H
#define INCLUDED_KEYBOARDSTATE_H

#include "layerstack.h"
#include "macroset.h"
#include "lockset.h"

class KeyboardState
{
public:
    constexpr KeyboardState() = default;

public:
    LayerStack layerStack;
    MacroSet   macroSet;
    LockSet    lockSet;
    
private:
    KeyboardState(const KeyboardState&);
    KeyboardState& operator=(const KeyboardState&);    
};

#endif
