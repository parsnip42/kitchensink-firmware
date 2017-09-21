#include "serialize/serializer.h"

#include "layer.h"
#include "layerstack.h"
#include "event/event.h"
#include "serialize/eventserializer.h"
#include "data/keycode.h"
#include "types/strutil.h"
#include "types/stroutstream.h"
#include "types/instream.h"
#include "types/outstream.h"
#include "globalconfig.h"
#include "config.h"

#include "serialize/iniformat.h"

#include "mbedtls/aes.h"

void Serializer<GlobalConfig>::serialize(const GlobalConfig& globalConfig, OutStream& os)
{
    IniFormat::OStream ini(os);
    
    ini.writeSection("config");

    auto writeProperty([&](const StrRef& key, int value)
    {
        StrBuf<32> valueStr;
        StrOutStream ostream(valueStr);

        ostream.appendInt(value);
        
        ini.writeProperty(key, valueStr);
    });

    writeProperty("tapDelay", globalConfig.tapDelay);
    writeProperty("keyRepeatDelay", globalConfig.keyRepeatDelay);
    writeProperty("keyRepeatRate", globalConfig.keyRepeatRate);
    writeProperty("homeScreenColumns", globalConfig.homeScreenColumns);
    writeProperty("homeScreenTimeout", globalConfig.homeScreenTimeout);

    const auto& homeLedSet(globalConfig.homeLedSet);
    
    for (std::size_t i(0); i < homeLedSet.size(); ++i)
    {
        StrBuf<20> headerStr;
        StrOutStream ostream(headerStr);

        ostream.appendStr("home ")
               .appendInt(i);
                                
        ini.writeSection(headerStr);

        const auto& homeLed(homeLedSet[i]);
        
        writeProperty("type", static_cast<int>(homeLed.type));
        writeProperty("index", homeLed.index);
    }
}

bool Serializer<GlobalConfig>::deserialize(InStream& is, GlobalConfig& globalConfig)
{
    IniFormat::IStream ini(is);

    StrRef sectionName;

    auto& homeLedSet(globalConfig.homeLedSet);

    while (ini.nextSection(sectionName))
    {
        int homeLedId;
        StrRef typeStr;
        StrRef numStr;

        if (StrUtil::cutTrim(sectionName, typeStr, ' ', numStr) &&
            typeStr == "home" &&
            StrUtil::parseUInt(numStr, homeLedId))
        {
            auto& homeLed(homeLedSet[homeLedId]);

            StrRef key;
            StrRef value;
            
            while (ini.nextProperty(key, value))
            {
                if (key == "type")
                {
                    int typeValue(0);

                    if (StrUtil::parseUInt(value, typeValue))
                    {
                        homeLed.type = static_cast<HomeLed::Type>(typeValue);
                    }
                }
                else if (key == "index")
                {
                    int indexValue(0);

                    if (StrUtil::parseUInt(value, indexValue))
                    {
                        homeLed.index = indexValue;
                    }
                }
            }
        }
        else if (sectionName == "config")
        {
            StrRef key;
            StrRef value;
            
            while (ini.nextProperty(key, value))
            {
                auto readProperty([&](const StrRef& propertyKey,
                                      uint32_t&     propertyValue)
                {
                    if (key == propertyKey)
                    {
                        int intValue(0);
                        
                        if (StrUtil::parseUInt(value, intValue))
                        {
                            propertyValue = intValue;
                        }
                    }
                });

                readProperty("tapDelay", globalConfig.tapDelay);
                readProperty("keyRepeatDelay", globalConfig.keyRepeatDelay);
                readProperty("keyRepeatRate", globalConfig.keyRepeatRate);
                readProperty("homeScreenColumns", globalConfig.homeScreenColumns);
                readProperty("homeScreenTimeout", globalConfig.homeScreenTimeout);
            }
        }
    }
    
    return true;
}

void Serializer<MacroSet>::serialize(const MacroSet& macroSet, OutStream& os)
{
    IniFormat::OStream ini(os);

    for (std::size_t i(0); i < macroSet.size(); ++i)
    {
        StrBuf<20> headerStr;
        StrOutStream ostream(headerStr);

        ostream.appendStr("macro ")
               .appendInt(i);
                                
        ini.writeSection(headerStr);

        const auto& macro(macroSet[i]);
        
        ini.writeProperty("name", macro.name);
        ini.writeProperty("shortcut", macro.shortcut);

        StrBuf<12> typeStr;
        StrOutStream oss(typeStr);

        oss.appendInt(static_cast<int>(macro.type));
    
        ini.writeProperty("type", typeStr);

        os.write("content=");

        for (const auto& event : macro.content)
        {
            StrBuf<24> str;

            EventSerializer::serialize(event, str);
        
            os.write(str);
            os.write(" ");
        }

        os.write("\n");
    }    
}

bool Serializer<MacroSet>::deserialize(InStream& is, MacroSet& macroSet)
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

            std::array<Event, Config::kMacroMaxSize> macroData;
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

                    macro.type = static_cast<Macro::Type>(typeVal);
                }

                if (key == "content")
                {
                    StrRef token(StrUtil::nextToken(value, " \t"));
                    
                    while (!token.empty() && macroDataSize < macroData.size())
                    {
                        auto& event(macroData[macroDataSize++]);

                        EventSerializer::deserialize(token, event);
                        
                        token = StrUtil::nextToken(value, " \t", token);
                    }
                }

                macro.content.assign(macroData.begin(),
                                     macroData.begin() + macroDataSize); 
            }
        }
    }
    
    return false;
}

void Serializer<SecureMacroSet>::serialize(const SecureMacroSet& macroSet, OutStream& os)
{
    IniFormat::OStream ini(os);

    for (std::size_t i(0); i < macroSet.size(); ++i)
    {
        StrBuf<20> headerStr;
        StrOutStream ostream(headerStr);

        ostream.appendStr("macro ")
               .appendInt(i);
                                
        ini.writeSection(headerStr);

        const auto& macro(macroSet[i]);
        
        ini.writeProperty("name", macro.name);
        ini.writeProperty("shortcut", macro.shortcut);

        StrBuf<12> typeStr;
        StrOutStream oss(typeStr);

        oss.appendInt(static_cast<int>(macro.type));
    
        ini.writeProperty("type", typeStr);

        os.write("content=");

        for (const auto& event : macro.content)
        {
            StrBuf<24> str;

            EventSerializer::serialize(event, str);
        
            os.write(str);
            os.write(" ");
        }

        os.write("\n");
    }    
}

bool Serializer<SecureMacroSet>::deserialize(InStream& is, SecureMacroSet& macroSet)
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

            std::array<Event, Config::kMacroMaxSize> macroData;
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

                    macro.type = static_cast<Macro::Type>(typeVal);
                }

                if (key == "content")
                {
                    StrRef token(StrUtil::nextToken(value, " \t"));
                    
                    while (!token.empty() && macroDataSize < macroData.size())
                    {
                        auto& event(macroData[macroDataSize++]);

                        EventSerializer::deserialize(token, event);
                        
                        token = StrUtil::nextToken(value, " \t", token);
                    }
                }

                macro.content.assign(macroData.begin(),
                                     macroData.begin() + macroDataSize); 
            }
        }
    }
    
    return false;
}

void Serializer<LayerStack>::serialize(const LayerStack& layerStack, OutStream& os)
{
    IniFormat::OStream ini(os);

    int layerIndex(0);
    
    for (const auto& layer : layerStack)
    {
        StrBuf<20> headerStr;
        StrOutStream ostream(headerStr);

        ostream.appendStr("layer ")
               .appendInt(layerIndex++);
                                
        ini.writeSection(headerStr);
        ini.writeProperty("name", layer.name);

        for (const auto& row : layer.mapping)
        {
            os.write("row=");
        
            for (const auto& event : row)
            {
                StrBuf<24> str;
            
                EventSerializer::serialize(event, str);
            
                os.write(str);
                os.write(" ");
            }
        
            os.write("\n");
        }

        os.write("\n");
    }
}

bool Serializer<LayerStack>::deserialize(InStream& is, LayerStack& layerStack)
{
    IniFormat::IStream ini(is);

    StrRef sectionName;

    while (ini.nextSection(sectionName))
    {
        int layerId;
        StrRef typeStr;
        StrRef numStr;

        if (StrUtil::cutTrim(sectionName, typeStr, ' ', numStr) &&
            typeStr == "layer" &&
            StrUtil::parseUInt(numStr, layerId))
        {
            auto& layer(layerStack[layerId]);

            StrRef key;
            StrRef value;

            std::size_t rowIndex(0);
            
            while (ini.nextProperty(key, value))
            {
                if (key == "name")
                {
                    layer.name = value;
                }
                else if (key == "row")
                {
                    if (rowIndex < layer.mapping.size())
                    {
                        auto& row(layer.mapping[rowIndex++]);
                        auto token(StrUtil::nextToken(value, " \t"));

                        std::size_t index(0);
        
                        while (!token.empty() && index < row.size())
                        {
                            EventSerializer::deserialize(token, row[index++]);
                            token = StrUtil::nextToken(value, " \t", token);
                        }
                    }
                }
            }
        }
    }

    return true;
}

void Serializer<MultiKeySet>::serialize(const MultiKeySet& multiKeySet, OutStream& os)
{
    IniFormat::OStream ini(os);

    int index(0);
    
    for (const auto& multiKey : multiKeySet)
    {
        StrBuf<20> headerStr;
        StrOutStream ostream(headerStr);

        ostream.appendStr("multi ")
               .appendInt(index++);
                                
        ini.writeSection(headerStr);

        ini.writeProperty("name", multiKey.name);

        for (const auto& event : multiKey.events)
        {
            StrBuf<24> str;
            
            EventSerializer::serialize(event, str);

            ini.writeProperty("event", str);
        }
    }
}

bool Serializer<MultiKeySet>::deserialize(InStream& is, MultiKeySet& multiKeySet)
{
    IniFormat::IStream ini(is);

    StrRef sectionName;

    while (ini.nextSection(sectionName))
    {
        int multiId;
        StrRef typeStr;
        StrRef numStr;

        if (StrUtil::cutTrim(sectionName, typeStr, ' ', numStr) &&
            typeStr == "multi" &&
            StrUtil::parseUInt(numStr, multiId))
        {
            auto& multiKey(multiKeySet[multiId]);

            StrRef key;
            StrRef value;

            std::size_t eventIndex(0);
            
            while (ini.nextProperty(key, value))
            {
                if (key == "name")
                {
                    multiKey.name = value;
                }
                else if (key == "event")
                {
                    if (eventIndex < multiKey.events.size())
                    {
                        EventSerializer::deserialize(value,
                                                     multiKey.events[eventIndex++]);
                    }
                }
            }
        }
    }

    return true;
}

void Serializer<SmartKeySet>::serialize(const SmartKeySet& smartKeySet, OutStream& os)
{
    IniFormat::OStream ini(os);

    int index(0);
    
    for (const auto& smartKey : smartKeySet)
    {
        StrBuf<20> headerStr;
        StrOutStream ostream(headerStr);

        ostream.appendStr("smart ")
               .appendInt(index++);
                                
        ini.writeSection(headerStr);

        ini.writeProperty("name", smartKey.name);

        {
            StrBuf<24> str;
            
            EventSerializer::serialize(smartKey.event, str);

            ini.writeProperty("event", str);
        }

        {
            StrBuf<24> str;
            
            EventSerializer::serialize(smartKey.auxEvent, str);

            ini.writeProperty("auxEvent", str);
        }
    }
}

bool Serializer<SmartKeySet>::deserialize(InStream& is, SmartKeySet& smartKeySet)
{
    IniFormat::IStream ini(is);

    StrRef sectionName;

    while (ini.nextSection(sectionName))
    {
        int smartId;
        StrRef typeStr;
        StrRef numStr;

        if (StrUtil::cutTrim(sectionName, typeStr, ' ', numStr) &&
            typeStr == "smart" &&
            StrUtil::parseUInt(numStr, smartId))
        {
            auto& smartKey(smartKeySet[smartId]);

            StrRef key;
            StrRef value;

            while (ini.nextProperty(key, value))
            {
                if (key == "name")
                {
                    smartKey.name = value;
                }
                else if (key == "event")
                {
                    EventSerializer::deserialize(value,
                                                 smartKey.event);
                }
                else if (key == "auxEvent")
                {
                    EventSerializer::deserialize(value,
                                                 smartKey.auxEvent);
                }
            }
        }
    }

    return true;
}
