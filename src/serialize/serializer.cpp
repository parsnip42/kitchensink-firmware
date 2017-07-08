#include "serializer.h"

#include "layer.h"
#include "keyid.h"
#include "layerstack.h"
#include "keyevent.h"

#include "data/keycodes.h"

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

    Serializer<Layer::Row> s;
        
    for (const auto& row : layer.mapping)
    {        
        s.serialize(row, os);
        os.write("\n");
    }

    os.write("\n");
}
    
bool Serializer<Layer>::deserialize(Storage::IStream& is, Layer& layer)
{
    return true;
}

void Serializer<KeyId>::serialize(const KeyId& keyId, Storage::OStream& os)
{
    switch (keyId.type())
    {
    case KeyId::Type::kKey:
        if (keyId.value() != 0)
        {
            os.write("K");

            auto keyName(KeyCodes::keyName(keyId.value()));

            if (!keyName.empty())
            {
                os.write(keyName);
            }
            else
            {
                StrBuf<12> str;

                str.appendChar('x');
                str.appendInt(keyId.value(), "%x");
                
                os.write(str);                
            }
        }
        else
        {
            os.write("_");
        }
        break;

    case KeyId::Type::kMacro:
        os.write("M");
        {
            StrBuf<12> str;

            str.appendInt(keyId.value());

            os.write(str);
        }
        break;
            
    case KeyId::Type::kLayer:
        os.write("L");
        {
            StrBuf<12> str;

            str.appendInt(keyId.value());

            os.write(str);
        }
        break;

    default:
        os.write("");
        break;
    }
}
    
void Serializer<KeyEvent>::serialize(const KeyEvent& keyEvent, Storage::OStream& os)
{
    Serializer<KeyId> s;

    if (!keyEvent.pressed)
    {
        os.write("!");
    }
    
    s.serialize(keyEvent.keyId, os);
}

bool Serializer<KeyEvent>::deserialize(Storage::IStream& is, KeyEvent& keyEvent)
{
    return true;
}









