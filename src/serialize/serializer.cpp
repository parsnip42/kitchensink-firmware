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

    Serializer<Macro> s;
    
    for (std::size_t i(0); i < macroSet.size(); ++i)
    {
        StrBuf<20> headerStr;
        StrOStream ostream(headerStr);

        ostream.appendStr("macro ")
               .appendInt(i);
                                
        ini.writeSection(headerStr);
        s.serialize(macroSet[i], os);
    }    
}

bool Serializer<MacroSet>::deserialize(Storage::IStream& is, MacroSet& macroSet)
{
    IniFormat::IStream ini(is);
    
    StrRef sectionName;

    while (ini.nextSection(sectionName))
    {
        int macroId;
        StrRef typeStr;
        StrRef numStr;

        if (StrUtil::cutTrim(sectionName, typeStr, ' ', numStr) &&
            typeStr == "macro" &&
            StrUtil::parseUInt(numStr, macroId))
        {
            auto& macro(macroSet[macroId]);
            
            StrRef key;
            StrRef value;

            std::array<KeyEvent, 200> macroData;
            std::size_t macroDataSize(0);

            while (ini.nextProperty(key, value))
            {
                if (key == "name")
                {
                    macro.name = value;
                }

                if (key == "shortcut")
                {
                    macro.shortcut = value;
                }

                if (key == "type")
                {
                    int typeVal;
                    
                    StrUtil::parseUInt(value, typeVal);

                    macro.type = static_cast<MacroType>(typeVal);
                }

                if (key == "content")
                {
                    StrRef token(StrUtil::nextToken(value, " \t"));
                    
                    while (!token.empty() && macroDataSize < macroData.size())
                    {
                        auto& keyEvent(macroData[macroDataSize++]);
                        
                        if (token.beginsWith("!"))
                        {
                            token = token.substr(1);
                            keyEvent.pressed = false;
                        }
                        else
                        {
                            keyEvent.pressed = true;
                        }
                        
                        KeyIdSerializer::deserialize(token, keyEvent.keyId);
                        token = StrUtil::nextToken(value, " \t", token);
                    }
                }

                macro.setContent(macroData.begin(), macroData.begin() + macroDataSize); 
            }
        }
    }
    
    return false;
}

void Serializer<Macro>::serialize(const Macro& macro, Storage::OStream& os)
{
    IniFormat::OStream ini(os);

    ini.writeProperty("name", macro.name);
    ini.writeProperty("shortcut", macro.shortcut);

    StrBuf<12> typeStr;
    StrOStream oss(typeStr);

    oss.appendInt(static_cast<int>(macro.type));
    
    ini.writeProperty("type", typeStr);

    os.write("content=");

    for (const auto& event : macro.content())
    {
        if (!event.pressed)
        {
            os.write("!");
        }
        
        StrBuf<24> str;

        KeyIdSerializer::serialize(event.keyId, str);
        os.write(str);
        
        os.write(" ");
    }

    os.write("\n");
}

bool Serializer<Macro>::deserialize(Storage::IStream& is, Macro& macro)
{
    return true;
}

void Serializer<Layer>::serialize(const Layer& layer, Storage::OStream& os)
{
    IniFormat::OStream ini(os);
    
    ini.writeProperty("name", layer.name);

    for (const auto& row : layer.mapping)
    {
        os.write("row=");
        
        for (const auto& key : row)
        {
            StrBuf<24> str;
            
            KeyIdSerializer::serialize(key, str);
            
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
    
    is.readLine(layer.name);

    for (auto& row : layer.mapping)
    {
        StrBuf<240> rowData;
        
        is.readLine(rowData);

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