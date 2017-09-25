#include "serialize/eventserializer.h"

#include "event/event.h"
#include "event/keyevent.h"
#include "event/actionevent.h"
#include "event/delayevent.h"
#include "event/multievent.h"
#include "event/screenevent.h"
#include "event/layerevent.h"
#include "event/ledmaskevent.h"
#include "event/macroevent.h"
#include "event/smartevent.h"
#include "event/tickevent.h"
#include "types/strutil.h"
#include "data/keycode.h"
#include "data/keycodeutil.h"

namespace EventSerializer
{

namespace
{

void serialize(const ActionEvent& event, const StrOutStream& os)
{
    os.appendChar('A');
    os.appendInt(static_cast<int>(event.type));
}

void serialize(const DelayEvent& event, const StrOutStream& os)
{
    os.appendChar('D');
    os.appendInt(static_cast<int>(event.delayMs));
}

void serialize(const KeyEvent& event, const StrOutStream& os)
{
    os.appendChar('K');

    auto keyName(KeyCodeUtil::keyName(event.key));

    if (!keyName.empty())
    {
        os.appendStr(keyName);
    }
    else
    {
        os.appendChar('_');
        os.appendInt(static_cast<int>(event.key));
    }
}

void serialize(const LayerEvent& event, const StrOutStream& os)
{
    os.appendChar('L');
    os.appendInt(event.layer);
}

void serialize(const MacroEvent& event, const StrOutStream& os)
{
    os.appendChar('M');

    switch (event.type)
    {
    case MacroEvent::Type::kSecure:
        os.appendChar('S');
        break;
        
    case MacroEvent::Type::kDefault:
    default:
        os.appendChar('D');
        break;
    }    

    os.appendInt(event.macroId);
}

void serialize(const MultiEvent& event, const StrOutStream& os)
{
    os.appendChar('N');
    os.appendInt(event.multiId);
}

void serialize(const ScreenEvent& event, const StrOutStream& os)
{
    os.appendChar('U');
    os.appendInt(static_cast<int>(event.type));
    os.appendChar(':');
    os.appendInt(event.index);
}

void serialize(const SmartEvent& event, const StrOutStream& os)
{
    os.appendChar('S');
    os.appendInt(event.smartId);
}

}

void serialize(const Event& event, const StrOutStream& os)
{
    if (event == Event())
    {
        os.appendChar('_');
        return;
    }
    
    if (event.inverted())
    {
        os.appendChar('!');
    }

    if (event.is<ActionEvent>())
    {
        serialize(event.get<ActionEvent>(), os);
    }
    else if (event.is<DelayEvent>())
    {
        serialize(event.get<DelayEvent>(), os);
    }
    else if (event.is<KeyEvent>())
    {
        serialize(event.get<KeyEvent>(), os);
    }
    else if (event.is<LayerEvent>())
    {
        serialize(event.get<LayerEvent>(), os);
    }
    else if (event.is<MacroEvent>())
    {
        serialize(event.get<MacroEvent>(), os);
    }
    else if (event.is<MultiEvent>())
    {
        serialize(event.get<MultiEvent>(), os);
    }
    else if (event.is<ScreenEvent>())
    {
        serialize(event.get<ScreenEvent>(), os);
    }
    else if (event.is<SmartEvent>())
    {
        serialize(event.get<SmartEvent>(), os);
    }
    else
    {
        os.appendChar('_');
    }
}

void deserialize(const StrRef& eventStr, Event& event)
{
    if (eventStr.empty())
    {
        return;
    }

    switch (eventStr[0])
    {
    case '!':
    {
        deserialize(eventStr.substr(1), event);
        event = event.invert();
        break;
    }

    case 'A':
    {
        int index(0);

        if (StrUtil::parseUInt(eventStr.substr(1), index))
        {
            event = ActionEvent::create(static_cast<ActionEvent::Type>(index));
        }

        break;
    }
    
    case 'D':
    {
        int delayMs(0);

        if (StrUtil::parseUInt(eventStr.substr(1), delayMs))
        {
            event = DelayEvent::create(delayMs);
        }
        
        break;
    }

    case 'K':
    {
        auto keyCodeStr(eventStr.substr(1));

        if (!keyCodeStr.empty() && keyCodeStr[0] == '_')
        {
            int index(0);

            if (StrUtil::parseUInt(keyCodeStr.substr(1), index))
            {
                event = KeyEvent::create(static_cast<KeyCode>(index));
            }
        }
        else
        {
            auto key(KeyCodeUtil::keyCode(keyCodeStr));
            
            if (key != KeyCode::None)
            {
                event = KeyEvent::create(key);
            }
        }
        
        break;
    }
    
    case 'L':
    {
        int index(0);

        if (StrUtil::parseUInt(eventStr.substr(1), index))
        {
            event = LayerEvent::create(index);
        }
        
        break;
    }

    case 'M':
    {
        auto type(MacroEvent::Type::kDefault);
        int index(0);

        switch (eventStr[1])
        {
        case 'S':
            type = MacroEvent::Type::kSecure;
            break;

        case 'D':
        default:
            type = MacroEvent::Type::kDefault;
            break;
        }
        
        if (StrUtil::parseUInt(eventStr.substr(2), index))
        {
            event = MacroEvent::create(type, index);
        }
        
        break;
    }
    
    case 'N':
    {
        int index(0);

        if (StrUtil::parseUInt(eventStr.substr(1), index))
        {
            event = MultiEvent::create(index);
        }
        
        break;
    }
    
    case 'U':
    {
        int type(0);

        auto contentStr(eventStr.substr(1));
        auto token(StrUtil::nextToken(contentStr, ":"));

        if (StrUtil::parseUInt(token, type))
        {
            token = StrUtil::nextToken(contentStr, ":", token);

            int index(0);
            
            if (StrUtil::parseUInt(token, index))
            {
                event = ScreenEvent::create(static_cast<ScreenEvent::Type>(type),
                                            index);
            }
        }
        break;
    }
    
    case 'S':
    {
        int index(0);

        if (StrUtil::parseUInt(eventStr.substr(1), index))
        {
            event = SmartEvent::create(index);
        }
        
        break;
    }

    }
}

namespace
{

void serializeReadable(const ActionEvent& event, const StrOutStream& os)
{
    os.appendStr("Action ");
    os.appendInt(static_cast<int>(event.type));
}

void serializeReadable(const DelayEvent& event, const StrOutStream& os)
{
    os.appendStr("Delay ");
    os.appendInt(event.delayMs);
}

void serializeReadable(const KeyEvent& event, const StrOutStream& os)
{
    auto keyName(KeyCodeUtil::keyName(event.key));

    if (!keyName.empty())
    {
        os.appendStr(keyName);
    }
    else
    {
        os.appendStr("0x");
        os.appendInt(static_cast<uint8_t>(event.key), "%2.2x");
    }
}

void serializeReadable(const LayerEvent& event, const StrOutStream& os)
{
    os.appendStr("Layer ");
    os.appendInt(event.layer);
}

void serializeReadable(const LedMaskEvent& event, const StrOutStream& os)
{
    os.appendStr("LED ");
    os.appendChar(event.numLock() ? 'N' : '-');
    os.appendChar(event.capsLock() ? 'C' : '-');
    os.appendChar(event.scrollLock() ? 'S' : '-');
}

void serializeReadable(const MacroEvent& event, const StrOutStream& os)
{
    switch (event.type)
    {
    case MacroEvent::Type::kSecure:
        os.appendStr("Secure Macro ");
        break;
        
    case MacroEvent::Type::kDefault:
    default:
        os.appendStr("Macro ");
        break;
    }    

    os.appendInt(event.macroId);
}

void serializeReadable(const MultiEvent& event, const StrOutStream& os)
{
    os.appendStr("Multi ");
    os.appendInt(event.multiId);
}

void serializeReadable(const ScreenEvent& event, const StrOutStream& os)
{
    os.appendStr("Screen ");
    os.appendInt(static_cast<int>(event.type));
    os.appendChar(':');
    os.appendInt(event.index);
}

void serializeReadable(const SmartEvent& event, const StrOutStream& os)
{
    os.appendStr("Smart ");
    os.appendInt(event.smartId);
}

void serializeReadable(const TickEvent& event, const StrOutStream& os)
{
    os.appendStr("Tick ");
    os.appendInt(event.tickId);
}

}

void serializeReadable(const Event& event, const StrOutStream& os)
{
    if (event.inverted())
    {
        os.appendChar('!');
    }
    
    if (event.is<ActionEvent>())
    {
        serializeReadable(event.get<ActionEvent>(), os);
    }
    else if (event.is<DelayEvent>())
    {
        serializeReadable(event.get<DelayEvent>(), os);
    }
    else if (event.is<KeyEvent>())
    {
        serializeReadable(event.get<KeyEvent>(), os);
    }
    else if (event.is<LayerEvent>())
    {
        serializeReadable(event.get<LayerEvent>(), os);
    }
    else if (event.is<LedMaskEvent>())
    {
        serializeReadable(event.get<LedMaskEvent>(), os);
    }
    else if (event.is<MacroEvent>())
    {
        serializeReadable(event.get<MacroEvent>(), os);
    }
    else if (event.is<MultiEvent>())
    {
        serializeReadable(event.get<MultiEvent>(), os);
    }
    else if (event.is<ScreenEvent>())
    {
        serializeReadable(event.get<ScreenEvent>(), os);
    }
    else if (event.is<SmartEvent>())
    {
        serializeReadable(event.get<SmartEvent>(), os);
    }
    else if (event.is<TickEvent>())
    {
        serializeReadable(event.get<TickEvent>(), os);
    }
    else
    {
        os.appendStr("?");
    }
}

}
