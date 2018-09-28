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

enum class StorageResult
{
    OK,
    StorageError,
    CryptoError,
    EntropyError
};

void load(KeyboardState& keyboardState);

StorageResult load(GlobalConfig& globalConfig);
StorageResult load(MacroSet& macroSet);
StorageResult load(LayerStack& layerStack);
StorageResult load(MultiKeySet& multiKeySet);
StorageResult load(SmartKeySet& smartKeySet);

StorageResult load(SecureMacroSet& secureMacroSet,
                   const StrRef& password);

void store(const KeyboardState& keyboardState);

StorageResult store(const GlobalConfig& globalConfig);
StorageResult store(const MacroSet& macroSet);
StorageResult store(const LayerStack& layerStack);
StorageResult store(const MultiKeySet& multiKeySet);
StorageResult store(const SmartKeySet& smartKeySet);

StorageResult store(const SecureMacroSet& secureMacroSet,
                    EntropyPool&          entropyPool);

}

#endif
