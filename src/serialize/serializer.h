#ifndef INCLUDED_SERIALIZER_H
#define INCLUDED_SERIALIZER_H

#include "keyid.h"
#include "layer.h"
#include "layerstack.h"

#include "data/keycodes.h"
#include "storage/storage.h"

#include "types/strbuf.h"
#include "types/strref.h"

#include <array>

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
    
    bool deserialize(Storage::IStream&, std::array<T, N>&)
    {
        return true;
    }
};

template <>
struct Serializer<Layer>
{
    void serialize(const Layer& layer, Storage::OStream& os)
    {
        os.write(layer.name);
        os.write("\n");
        
        for (const auto& row : layer.mapping)
        {
            Serializer<Layer::Row> s;
            
            s.serialize(row, os);
            os.write("\n");
        }
    }
    
    bool deserialize(Storage::IStream&, KeyId&)
    {
        return true;
    }
};

template <>
struct Serializer<LayerStack>
{
    void serialize(const LayerStack& layerStack, Storage::OStream& os)
    {
        for (std::size_t i(0); i < LayerStack::MaxLayers; ++i)
        {
            os.write("[Layer]");

            Serializer<Layer> s;

            s.serialize(layerStack[i], os);
            os.write("\n");
        }
    }
    
    bool deserialize(Storage::IStream&, KeyId&)
    {
        return true;
    }
};

template <>
struct Serializer<KeyId>
{
    void serialize(const KeyId& keyId, Storage::OStream& os)
    {
        switch (keyId.type())
        {
        case KeyId::Type::kKey:
            if (keyId.value() != 0)
            {
                os.write("K_");
                os.write(KeyCodes::keyName(keyId.value()));
            }
            else
            {
                os.write("_");
            }
            break;

        case KeyId::Type::kMacro:
            os.write("M_");
            {
                StrBuf<12> str;

                str.appendInt(keyId.value());

                os.write(str);
            }
            break;
            
        case KeyId::Type::kLayer:
            os.write("L_");
            {
                StrBuf<12> str;

                str.appendInt(keyId.value());

                os.write(str);
            }
            break;
            
        default:
            os.write("_");
            break;
        }
    }
    
    bool deserialize(Storage::IStream&, KeyId&)
    {
        return true;
    }
};

#endif /* INCLUDED_SERIALIZER_H */
