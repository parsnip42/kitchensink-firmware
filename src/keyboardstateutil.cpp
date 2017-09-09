#include "keyboardstateutil.h"

#include "keyboardstate.h"
#include "storage/storage.h"
#include "serialize/serializer.h"

namespace KeyboardStateUtil
{

void load(KeyboardState& keyboardState)
{
    Storage storage;
    
    auto is(storage.read(Storage::Region::kMacro));
    Serializer<MacroSet> s;
    
    s.deserialize(is, keyboardState.macroSet);
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

}
