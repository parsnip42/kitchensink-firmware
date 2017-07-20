#ifndef INCLUDED_KEYBOARDSTATE_H
#define INCLUDED_KEYBOARDSTATE_H

#include "layerstack.h"
#include "macroset.h"
#include "multiset.h"
#include "lockset.h"

class KeyboardState
{
public:
    KeyboardState() = default;

public:
    LayerStack layerStack;
    MacroSet   macroSet;
    MultiSet   multiSet;
    LockSet    lockSet;
    
private:
    KeyboardState(const KeyboardState&) = delete;
    KeyboardState& operator=(const KeyboardState&) = delete;
};

#endif
