#ifndef INCLUDED_KEYBOARDSTATEUTIL_H
#define INCLUDED_KEYBOARDSTATEUTIL_H

#include "multikeyset.h"
#include "smartkeyset.h"

class KeyboardState;
class MacroSet;
class LayerStack;

namespace KeyboardStateUtil
{

void load(KeyboardState& keyboardState);
void store(const MacroSet& macroSet);
void store(const LayerStack& layerStack);

void store(const MultiKeySet& multiKeySet);
void store(const SmartKeySet& smartKeySet);

}

#endif
