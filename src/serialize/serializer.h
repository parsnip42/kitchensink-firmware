#ifndef INCLUDED_SERIALIZER_H
#define INCLUDED_SERIALIZER_H

#include "storage/storage.h"
#include "types/strbuf.h"
#include "types/strref.h"
#include "types/range.h"
#include "macroset.h"

#include <array>

class KeyEvent;
class KeyId;
class Layer;

template <typename T>
struct Serializer
{
    void serialize(const T&, Storage::OStream&);
    bool deserialize(Storage::IStream&, T&);
};

template <typename T, std::size_t N>
struct Serializer<std::array<T, N>>
{
    void serialize(const std::array<T, N>& array, Storage::OStream& os)
    {
        Serializer<T> s;
        
        for (const auto& element : array)
        {
            s.serialize(element, os);
            os.write(" ");
        }
    }
    
    bool deserialize(Storage::IStream& is, std::array<T, N>& array)
    {
        return true;
    }
};

template <>
struct Serializer<MacroSet::Macro>
{
    void serialize(const MacroSet::Macro& macro, Storage::OStream& os);
    bool deserialize(Storage::IStream& is, MacroSet::Macro& macro);
};

template <>
struct Serializer<Layer>
{
    void serialize(const Layer& layer, Storage::OStream& os);
    bool deserialize(Storage::IStream& is, Layer& layer);
};

template <>
struct Serializer<KeyId>
{
    void serialize(const KeyId& keyId, Storage::OStream& os);
    bool deserialize(Storage::IStream& is, KeyId& keyId);
};

template <>
struct Serializer<KeyEvent>
{
    void serialize(const KeyEvent& keyEvent, Storage::OStream& os);
    bool deserialize(Storage::IStream& is, KeyEvent& keyEvent);
};

#endif /* INCLUDED_SERIALIZER_H */
