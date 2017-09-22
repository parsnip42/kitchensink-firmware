#include "keyboardstateutil.h"

#include "keyboardstate.h"
#include "storage/storage.h"
#include "crypto/cryptoinstream.h"
#include "crypto/cryptooutstream.h"
#include "serialize/serializer.h"

namespace KeyboardStateUtil
{

void load(KeyboardState& keyboardState)
{
    load(keyboardState.globalConfig);
    load(keyboardState.macroSet);
    load(keyboardState.layerStack);
    load(keyboardState.multiKeySet);
    load(keyboardState.smartKeySet);
}

void load(GlobalConfig& globalConfig)
{
    Storage storage;
    
    auto is(storage.read(Storage::Region::kConfig));
    Serializer<GlobalConfig> s;
    
    s.deserialize(is, globalConfig);
}

void load(MacroSet& macroSet)
{
    Storage storage;
    
    auto is(storage.read(Storage::Region::kMacro));
    Serializer<MacroSet> s;
    
    s.deserialize(is, macroSet);
}

void load(LayerStack& layerStack)
{
    Storage storage;
    
    auto is(storage.read(Storage::Region::kLayer));
    Serializer<LayerStack> s;
    
    s.deserialize(is, layerStack);
}

void load(MultiKeySet& multiKeySet)
{
    Storage storage;
    
    auto is(storage.read(Storage::Region::kMultiKey));
    Serializer<MultiKeySet> s;
    
    s.deserialize(is, multiKeySet);
}

void load(SmartKeySet& smartKeySet)
{
    Storage storage;
    
    auto is(storage.read(Storage::Region::kSmartKey));
    Serializer<SmartKeySet> s;
    
    s.deserialize(is, smartKeySet);
}

void load(SecureMacroSet& secureMacroSet)
{
    Storage storage;

    auto is(storage.read(Storage::Region::kSecureMacro));
    
    CryptoInStream cryptoIn(is, "test");
    
    Serializer<SecureMacroSet> s;
    
    s.deserialize(cryptoIn, secureMacroSet);
}

void store(const KeyboardState& keyboardState)
{
    store(keyboardState.globalConfig);
    store(keyboardState.macroSet);
    store(keyboardState.layerStack);
    store(keyboardState.multiKeySet);
    store(keyboardState.smartKeySet);
}

void store(const GlobalConfig& globalConfig)
{
    Storage storage;
    Serializer<GlobalConfig> s;
    
    auto os(storage.write(Storage::Region::kConfig));
    
    s.serialize(globalConfig, os);
}

void store(const MacroSet& macroSet)
{
    Storage storage;
    Serializer<MacroSet> s;
    
    auto os(storage.write(Storage::Region::kMacro));
    
    s.serialize(macroSet, os);
}

void store(const LayerStack& layerStack)
{
    Storage storage;
    Serializer<LayerStack> s;
    
    auto os(storage.write(Storage::Region::kLayer));
    
    s.serialize(layerStack, os);
}

void store(const MultiKeySet& multiKeySet)
{
    Storage storage;
    Serializer<MultiKeySet> s;
    
    auto os(storage.write(Storage::Region::kMultiKey));
    
    s.serialize(multiKeySet, os);
}

void store(const SmartKeySet& smartKeySet)
{
    Storage storage;
    Serializer<SmartKeySet> s;
    
    auto os(storage.write(Storage::Region::kSmartKey));
    
    s.serialize(smartKeySet, os);   
}

void store(const SecureMacroSet& secureMacroSet,
           EntropyPool&          entropyPool)
{
    Storage storage;

    auto output(storage.write(Storage::Region::kSecureMacro));
    
    CryptoOutStream os(output,
                       "test",
                       entropyPool);
    
    Serializer<SecureMacroSet> s;
    
    s.serialize(secureMacroSet, os);
}

}
