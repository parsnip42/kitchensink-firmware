#include "keyboardstateutil.h"

#include "keyboardstate.h"
#include "storage/storage.h"
#include "crypto/entropypool.h"
#include "crypto/cryptoinstream.h"
#include "crypto/cryptooutstream.h"
#include "serialize/serializer.h"
#include "types/arrayutil.h"

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

StorageResult load(GlobalConfig& globalConfig)
{
    Storage storage;
    
    auto is(storage.read(Storage::Region::kConfig));
    Serializer<GlobalConfig> s;
    
    s.deserialize(is, globalConfig);

    return StorageResult::OK;
}

StorageResult load(MacroSet& macroSet)
{
    Storage storage;
    
    auto is(storage.read(Storage::Region::kMacro));
    Serializer<MacroSet> s;
    
    s.deserialize(is, macroSet);

    return StorageResult::OK;
}

StorageResult load(LayerStack& layerStack)
{
    Storage storage;
    
    auto is(storage.read(Storage::Region::kLayer));
    Serializer<LayerStack> s;
    
    s.deserialize(is, layerStack);

    return StorageResult::OK;
}

StorageResult load(MultiKeySet& multiKeySet)
{
    Storage storage;
    
    auto is(storage.read(Storage::Region::kMultiKey));
    Serializer<MultiKeySet> s;
    
    s.deserialize(is, multiKeySet);

    return StorageResult::OK;
}

StorageResult load(SmartKeySet& smartKeySet)
{
    Storage storage;
    
    auto is(storage.read(Storage::Region::kSmartKey));
    Serializer<SmartKeySet> s;
    
    s.deserialize(is, smartKeySet);

    return StorageResult::OK;
}

StorageResult load(SecureMacroSet& secureMacroSet,
                   const StrRef&   password)
{
    Storage storage;

    auto is(storage.read(Storage::Region::kSecureMacro));
    
    CryptoInStream cryptoIn(is, password);

    if (cryptoIn.state() != CryptoInStream::State::kReading)
    {
        return StorageResult::CryptoError;
    }
    
    Serializer<SecureMacroSet> s;
    
    s.deserialize(cryptoIn, secureMacroSet);

    if (cryptoIn.state() != CryptoInStream::State::kValidated)
    {
        // Anything here is invalid.
        secureMacroSet.lock();
        
        return StorageResult::CryptoError;
    }
    
    return StorageResult::OK;
}

void store(const KeyboardState& keyboardState)
{
    store(keyboardState.globalConfig);
    store(keyboardState.macroSet);
    store(keyboardState.layerStack);
    store(keyboardState.multiKeySet);
    store(keyboardState.smartKeySet);
}

StorageResult store(const GlobalConfig& globalConfig)
{
    Storage storage;
    Serializer<GlobalConfig> s;
    
    auto os(storage.write(Storage::Region::kConfig));
    
    s.serialize(globalConfig, os);

    return StorageResult::OK;
}

StorageResult store(const MacroSet& macroSet)
{
    Storage storage;
    Serializer<MacroSet> s;
    
    auto os(storage.write(Storage::Region::kMacro));
    
    s.serialize(macroSet, os);

    return StorageResult::OK;
}

StorageResult store(const LayerStack& layerStack)
{
    Storage storage;
    Serializer<LayerStack> s;
    
    auto os(storage.write(Storage::Region::kLayer));
    
    s.serialize(layerStack, os);

    return StorageResult::OK;
}

StorageResult store(const MultiKeySet& multiKeySet)
{
    Storage storage;
    Serializer<MultiKeySet> s;
    
    auto os(storage.write(Storage::Region::kMultiKey));
    
    s.serialize(multiKeySet, os);

    return StorageResult::OK;
}

StorageResult store(const SmartKeySet& smartKeySet)
{
    Storage storage;
    Serializer<SmartKeySet> s;
    
    auto os(storage.write(Storage::Region::kSmartKey));
    
    s.serialize(smartKeySet, os);

    return StorageResult::OK;
}

StorageResult store(const SecureMacroSet& secureMacroSet,
                    EntropyPool&          entropyPool)
{
    /*
    if (!secureMacroSet.password.empty())
    {
        Storage storage;
        
        auto output(storage.write(Storage::Region::kSecureMacro));
        
        Crypto::IV iv;
        Crypto::IV dataIv;
        Crypto::Key dataKey;

        Crypto::SHA256 ivPair;

        if (!entropyPool.read(ivPair))
        {
            return StorageResult::EntropyError;
        }

        ArrayUtil<decltype(ivPair)>::split(ivPair, iv, dataIv);

        if (!entropyPool.read(dataKey))
        {
            return StorageResult::EntropyError;
        }
        
        CryptoOutStream os(output,
                           secureMacroSet.password,
                           iv,
                           dataIv,
                           dataKey);
        
        Serializer<SecureMacroSet> s;
        
        s.serialize(secureMacroSet, os);

        return StorageResult::OK;
    }
    else
    {
        return StorageResult::DataLockedError;
    }
    */

    return StorageResult::OK;
}

}
