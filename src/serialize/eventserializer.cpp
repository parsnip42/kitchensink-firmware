#include "serialize/eventserializer.h"

#include "event/event.h"
#include "event/keyevent.h"
#include "event/actionevent.h"
#include "event/delayevent.h"
#include "event/multievent.h"
#include "event/screenevent.h"
#include "event/layerevent.h"
#include "event/macroevent.h"
#include "event/smartevent.h"
#include "types/strutil.h"

namespace EventSerializer
{

namespace
{

void serialize(const KeyEvent& event, const StrOStream& os)
{
    if (!event.pressed)
    {
        os.appendChar('!');
    }
    
    os.appendChar('K');

    auto keyName(KeyCodes::keyName(event.keyCode));

    if (!keyName.empty())
    {
        os.appendStr(keyName);
    }
    else
    {
        os.appendChar('_');
        os.appendInt(event.keyCode);
    }
}

void serialize(const LayerEvent& event, const StrOStream& os)
{
    if (!event.enable)
    {
        os.appendChar('!');
    }
    
    os.appendChar('L');
    os.appendInt(event.layer);
}

void serialize(const MacroEvent& event, const StrOStream& os)
{
    if (!event.pressed)
    {
        os.appendChar('!');
    }
    
    os.appendChar('M');
    os.appendInt(event.macroId);
}

void serialize(const ActionEvent& event, const StrOStream& os)
{
    os.appendChar('A');
    os.appendInt(event.actionId);
}

void serialize(const DelayEvent& event, const StrOStream& os)
{
    os.appendChar('D');
    os.appendInt(static_cast<int>(event.delayMs));
}

}

void serialize(const Event& event, const StrOStream& os)
{
    if (event.is<KeyEvent>())
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
    else if (event.is<ActionEvent>())
    {
        serialize(event.get<ActionEvent>(), os);
    }
    else if (event.is<DelayEvent>())
    {
        serialize(event.get<DelayEvent>(), os);
    }
    else
    {
        os.appendStr("?");
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
    
    case 'K':
    {
        auto keyCodeStr(eventStr.substr(1));

        if (!keyCodeStr.empty() && keyCodeStr[0] == '_')
        {
            int index(0);

            if (StrUtil::parseUInt(keyCodeStr.substr(1), index))
            {
                event = KeyEvent::create(index);
            }
        }
        else
        {
            auto keyCode(KeyCodes::keyCode(keyCodeStr));
            
            if (keyCode != 0)
            {
                event = KeyEvent::create(keyCode);
            }
        }
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
        int index(0);

        if (StrUtil::parseUInt(eventStr.substr(1), index))
        {
            event = MacroEvent::create(index);
        }
        
        break;
    }
    
    case 'A':
    {
        int index(0);

        if (StrUtil::parseUInt(eventStr.substr(1), index))
        {
            event = ActionEvent::create(index);
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

    }
}

namespace
{

void serializeReadable(const KeyEvent& event, const StrOStream& os)
{
    auto keyName(KeyCodes::keyName(event.keyCode));

    if (!keyName.empty())
    {
        os.appendStr(keyName);
    }
    else
    {
        os.appendStr("0x");
        os.appendInt(event.keyCode, "%2.2x");
    }
}

void serializeReadable(const LayerEvent& event, const StrOStream& os)
{
    os.appendStr("Layer ");
    os.appendInt(event.layer);
}

void serializeReadable(const MacroEvent& event, const StrOStream& os)
{
    os.appendStr("Macro ");
    os.appendInt(event.macroId);
}

void serializeReadable(const ActionEvent& event, const StrOStream& os)
{
    os.appendStr("Action ");
    os.appendInt(event.actionId);
}

}

void serializeReadable(const Event& event, const StrOStream& os)
{
    if (event.is<KeyEvent>())
    {
        serializeReadable(event.get<KeyEvent>(), os);
    }
    else if (event.is<LayerEvent>())
    {
        serializeReadable(event.get<LayerEvent>(), os);
    }
    else if (event.is<MacroEvent>())
    {
        serializeReadable(event.get<MacroEvent>(), os);
    }
    else if (event.is<ActionEvent>())
    {
        serializeReadable(event.get<ActionEvent>(), os);
    }
    else
    {
        os.appendStr("?");
    }
}

}
