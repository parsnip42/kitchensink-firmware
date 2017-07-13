#include "serialize/keyidserializer.h"

#include "types/strutil.h"

void KeyIdSerializer::serialize(KeyId keyId, StrOStream& str)
{
    switch (keyId.type())
    {
    case KeyId::Type::kKey:
        if (keyId.value() != 0)
        {
            str.appendChar('K');

            auto keyName(KeyCodes::keyName(keyId.value()));

            if (!keyName.empty())
            {
                str.appendStr(keyName);
            }
            else
            {
                str.appendChar('_');
                str.appendInt(keyId.value());
            }
        }
        else
        {
            str.appendStr("_");
        }
        break;

    case KeyId::Type::kLayer:
        str.appendChar('L');
        str.appendInt(keyId.value());
        break;
        
    case KeyId::Type::kLock:
        str.appendChar('O');
        str.appendInt(static_cast<int>(keyId.lockType()));
        str.appendChar(':');
        str.appendInt(keyId.value());
        break;

    case KeyId::Type::kMacro:
        str.appendChar('M');
        str.appendInt(keyId.value());
        break;

    case KeyId::Type::kAction:
        str.appendChar('A');
        str.appendInt(static_cast<int>(keyId.actionType()));
        str.appendChar(':');
        str.appendInt(keyId.value());
        break;
        
    case KeyId::Type::kDelay:
        str.appendChar('D');
        str.appendInt(static_cast<int>(keyId.delayMs()));
        break;

    default:
        str.appendStr("?");
        break;
    }
}

void KeyIdSerializer::deserialize(const StrRef& keyIdStr, KeyId& keyId)
{
    if (keyIdStr.empty())
    {
        return;
    }

    switch (keyIdStr[0])
    {
    case 'K':
    {
        auto keyCodeStr(keyIdStr.substr(1));

        if (!keyCodeStr.empty() && keyCodeStr[0] == '_')
        {
            int index(0);

            if (StrUtil::parseUInt(keyCodeStr.substr(1), index))
            {
                keyId = KeyId(index);
            }
        }
        else
        {
            auto keyCode(KeyCodes::keyCode(keyCodeStr));
            
            if (keyCode != 0)
            {
                keyId = KeyId(keyCode);
            }
        }
        
        break;
    }
    
    case 'L':
    {
        int index(0);

        if (StrUtil::parseUInt(keyIdStr.substr(1), index))
        {
            keyId = KeyId::Layer(index);
        }
        
        break;
    }

    case 'O':
    {
        auto contentStr(keyIdStr.substr(1));
        auto token(StrUtil::nextToken(contentStr, ":"));

        int type(0);
        
        if (StrUtil::parseUInt(token, type))
        {
            token = StrUtil::nextToken(contentStr, ":", token);

            int index(0);
            
            if (StrUtil::parseUInt(token, index))
            {
                keyId = KeyId::Lock(static_cast<KeyId::LockType>(type),
                                    index);
            }
        }
        break;
    }
    
    case 'M':
    {
        int index(0);

        if (StrUtil::parseUInt(keyIdStr.substr(1), index))
        {
            keyId = KeyId::Macro(index);
        }
        
        break;
    }
    
    case 'A':
    {
        auto contentStr(keyIdStr.substr(1));
        auto token(StrUtil::nextToken(contentStr, ":"));

        int type(0);
        
        if (StrUtil::parseUInt(token, type))
        {
            token = StrUtil::nextToken(contentStr, ":", token);

            int index(0);
            
            if (StrUtil::parseUInt(token, index))
            {
                keyId = KeyId::Action(static_cast<KeyId::ActionType>(type),
                                      index);
            }
        }
        break;
    }
    
    case 'D':
    {
        int delayMs(0);

        if (StrUtil::parseUInt(keyIdStr.substr(1), delayMs))
        {
            keyId = KeyId::Delay(delayMs);
        }
        
        break;
    }
    
    }
}

