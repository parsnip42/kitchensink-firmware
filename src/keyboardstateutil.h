#ifndef INCLUDED_KEYBOARDSTATEUTIL_H
#define INCLUDED_KEYBOARDSTATEUTIL_H

#include "multikeyset.h"
#include "smartkeyset.h"

class KeyboardState;
class GlobalConfig;
class MacroSet;
class LayerStack;

namespace KeyboardStateUtil
{

void load(KeyboardState& keyboardState);

void load(GlobalConfig& globalConfig);
void load(MacroSet& macroSet);
void load(LayerStack& layerStack);
void load(MultiKeySet& multiKeySet);
void load(SmartKeySet& smartKeySet);

void store(const KeyboardState& keyboardState);

void store(const GlobalConfig& globalConfig);
void store(const MacroSet& macroSet);
void store(const LayerStack& layerStack);
void store(const MultiKeySet& multiKeySet);
void store(const SmartKeySet& smartKeySet);

}

#endif
