#ifndef INCLUDED_KEYBOARDSTATE_H
#define INCLUDED_KEYBOARDSTATE_H

#include "layerstack.h"
#include "macroset.h"
#include "lockset.h"

class KeyboardState
{
public:
    KeyboardState() = default;

public:
    LayerStack layerStack;
    MacroSet   macroSet;
    LockSet    lockSet;
    
private:
    KeyboardState(const KeyboardState&) = delete;
    KeyboardState& operator=(const KeyboardState&) = delete;
};

#endif
