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

}
