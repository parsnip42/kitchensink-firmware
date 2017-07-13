#include "serializer.h"

#include "layer.h"
#include "keyid.h"
#include "layerstack.h"
#include "keyevent.h"
#include "serialize/keyidserializer.h"
#include "data/keycodes.h"
#include "types/strutil.h"
#include "types/strostream.h"

#include "serialize/iniformat.h"


void Serializer<MacroSet>::serialize(const MacroSet& macroSet, Storage::OStream& os)
{
    IniFormat::OStream ini(os);

    for (std::size_t i(0); i < macroSet.size(); ++i)
    {
        Serializer<MacroSet::Macro> s;

        StrBuf<20> headerStr;
        StrOStream ostream(headerStr);

        ostream.appendStr("macro ").appendInt(i);
                                
        ini.writeSection(headerStr);
        s.serialize(macroSet[i], os);
    }    
}

bool Serializer<MacroSet>::deserialize(Storage::IStream& is, MacroSet& macroSet)
{
    return true;
}

void Serializer<MacroSet::Macro>::serialize(const MacroSet::Macro& macro, Storage::OStream& os)
{
    IniFormat::OStream ini(os);

    ini.writeProperty("name", macro.name());
    
    os.write("content=");

    for (const auto& event : macro.content())
    {
        if (!event.pressed)
        {
            os.write("!");
        }
        
        StrBuf<24> str;
        StrOStream out(str);

        KeyIdSerializer::serialize(event.keyId, out);
        os.write(str);
        
        os.write(" ");
    }

    os.write("\n");
}

bool Serializer<MacroSet::Macro>::deserialize(Storage::IStream& is, MacroSet::Macro& macro)
{
    return true;
}

void Serializer<Layer>::serialize(const Layer& layer, Storage::OStream& os)
{
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
    
    StrOStream ostream(layer.name);

    is.readLine(ostream);

    for (auto& row : layer.mapping)
    {
        StrBuf<240> rowData;
        StrOStream ostream(rowData);
        
        is.readLine(ostream);

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
