#include "serialize/eventserializer.h"

#include "event/event.h"
#include "types/strutil.h"

namespace EventSerializer
{

void serialize(const Event& event, const StrOStream& os)
{
    // switch (keyId.type())
    // {
    // case KeyId::Type::kKey:
    //     if (keyId.value() != 0)
    //     {
    //         os.appendChar('K');

    //         auto keyName(KeyCodes::keyName(keyId.value()));

    //         if (!keyName.empty())
    //         {
    //             os.appendStr(keyName);
    //         }
    //         else
    //         {
    //             os.appendChar('_');
    //             os.appendInt(keyId.value());
    //         }
    //     }
    //     else
    //     {
    //         os.appendStr("_");
    //     }
    //     break;

    // case KeyId::Type::kLayer:
    //     os.appendChar('L');
    //     os.appendInt(keyId.value());
    //     break;
        
    // case KeyId::Type::kMacro:
    //     os.appendChar('M');
    //     os.appendInt(keyId.value());
    //     break;

    // case KeyId::Type::kAction:
    //     os.appendChar('A');
    //     os.appendInt(keyId.value());
    //     break;
        
    // case KeyId::Type::kDelay:
    //     os.appendChar('D');
    //     os.appendInt(static_cast<int>(keyId.delayMs()));
    //     break;

    // default:
    //     os.appendStr("?");
    //     break;
    // }
}

void deserialize(const StrRef& keyIdStr, Event& event)
{
    // if (keyIdStr.empty())
    // {
    //     return;
    // }

    // switch (keyIdStr[0])
    // {
    // case 'K':
    // {
    //     auto keyCodeStr(keyIdStr.substr(1));

    //     if (!keyCodeStr.empty() && keyCodeStr[0] == '_')
    //     {
    //         int index(0);

    //         if (StrUtil::parseUInt(keyCodeStr.substr(1), index))
    //         {
    //             keyId = KeyId(index);
    //         }
    //     }
    //     else
    //     {
    //         auto keyCode(KeyCodes::keyCode(keyCodeStr));
            
    //         if (keyCode != 0)
    //         {
    //             keyId = KeyId(keyCode);
    //         }
    //     }
        
    //     break;
    // }
    
    // case 'L':
    // {
    //     int index(0);

    //     if (StrUtil::parseUInt(keyIdStr.substr(1), index))
    //     {
    //         keyId = KeyId::Layer(index);
    //     }
        
    //     break;
    // }

    // case 'M':
    // {
    //     int index(0);

    //     if (StrUtil::parseUInt(keyIdStr.substr(1), index))
    //     {
    //         keyId = KeyId::Macro(index);
    //     }
        
    //     break;
    // }
    
    // case 'A':
    // {
    //     int index(0);

    //     if (StrUtil::parseUInt(keyIdStr.substr(1), index))
    //     {
    //         keyId = KeyId::Action(index);
    //     }

    //     break;
    // }
    
    // case 'D':
    // {
    //     int delayMs(0);

    //     if (StrUtil::parseUInt(keyIdStr.substr(1), delayMs))
    //     {
    //         keyId = KeyId::Delay(delayMs);
    //     }
        
    //     break;
    // }
    
    // }
}

}
