#ifndef INCLUDED_KEYBOARDSTATEUTIL_H
#define INCLUDED_KEYBOARDSTATEUTIL_H

#include "multikeyset.h"
#include "smartkeyset.h"

class EntropyPool;
class GlobalConfig;
class KeyboardState;
class LayerStack;
class MacroSet;
class SecureMacroSet;

namespace KeyboardStateUtil
{

void load(KeyboardState& keyboardState);

void load(GlobalConfig& globalConfig);
void load(MacroSet& macroSet);
void load(LayerStack& layerStack);
void load(MultiKeySet& multiKeySet);
void load(SmartKeySet& smartKeySet);

bool load(SecureMacroSet& secureMacroSet,
          const StrRef& password);

void store(const KeyboardState& keyboardState);

void store(const GlobalConfig& globalConfig);
void store(const MacroSet& macroSet);
void store(const LayerStack& layerStack);
void store(const MultiKeySet& multiKeySet);
void store(const SmartKeySet& smartKeySet);

void store(const SecureMacroSet& secureMacroSet,
           EntropyPool&          entropyPool);

}

#endif
