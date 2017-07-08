#include "serializer.h"

#include "layer.h"
#include "keyid.h"
#include "layerstack.h"
#include "keyevent.h"
#include "serialize/keyidserializer.h"
#include "data/keycodes.h"
#include "types/strutil.h"
#include "types/strostream.h"

void Serializer<MacroSet::Macro>::serialize(const MacroSet::Macro& macro, Storage::OStream& os)
{
    os.write("[Macro]\n");
    os.write(macro.name());
    os.write("\n");

    Serializer<KeyEvent> s;

    for (const auto& event : macro.content())
    {
        s.serialize(event, os);
        os.write(" ");
    }

    os.write("\n\n");
}

bool Serializer<MacroSet::Macro>::deserialize(Storage::IStream& is, MacroSet::Macro& macro)
{
    return true;
}

void Serializer<Layer>::serialize(const Layer& layer, Storage::OStream& os)
{
    os.write("[Layer]\n");
    os.write(layer.name);
    os.write("\n");

    for (const auto& row : layer.mapping)
    {
        for (const auto& key : row)
        {
            StrBuf<24> str;

            StrOStream out(str);
            KeyIdSerializer::serialize(key, out);
            os.write(str);
            
            os.write(" ");
        }
        
        os.write("\n");
    }

    os.write("\n");
}
    
bool Serializer<Layer>::deserialize(Storage::IStream& is, Layer& layer)
{
    layer.clear();
    
    is.readToken(layer.name, "\r\n");

    for (auto& row : layer.mapping)
    {
        StrBuf<240> rowData;
        
        is.readToken(rowData, "\r\n");

        StrRef token(StrUtil::nextToken(rowData, " \t"));

        std::size_t index(0);
        
        while (!token.empty() && index < row.size())
        {
            KeyIdSerializer::deserialize(token, row[index++]);
            token = StrUtil::nextToken(rowData, " \t", token);
        }
    }
    
    return true;
}

void Serializer<KeyEvent>::serialize(const KeyEvent& keyEvent, Storage::OStream& os)
{
    // Serializer<KeyId> s;

    // if (!keyEvent.pressed)
    // {
    //     os.write("!");
    // }
    
    // s.serialize(keyEvent.keyId, os);
}

bool Serializer<KeyEvent>::deserialize(Storage::IStream& is, KeyEvent& keyEvent)
{
    // StrBuf<32> key;

    // is.readToken(key, " \t");

    // if (key[0] == '!')
    // {
    //     keyEvent.pressed = false;
    // }
    
    return true;
}
