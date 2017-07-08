#include "serialize/keyidserializer.h"

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
                str.appendChar('x');
                str.appendInt(keyId.value(), "%x");
            }
        }
        else
        {
            str.appendStr("_");
        }
        break;

    case KeyId::Type::kMacro:
        str.appendChar('M');
        str.appendInt(keyId.value());
        break;
            
    case KeyId::Type::kLayer:
        str.appendChar('L');
        str.appendInt(keyId.value());
        break;

    default:
        str.appendStr("_");
        break;
    }
}

void KeyIdSerializer::deserialize(const StrRef& keyIdStr, KeyId& keyId)
{
    if (keyIdStr.empty())
    {
        return;
    }

    switch (*keyIdStr.begin())
    {
    case 'K':
    {
        auto keyCode(KeyCodes::keyCode(StrRef(keyIdStr.begin() + 1,
                                              keyIdStr.end())));

        if (keyCode != 0)
        {
            keyId = KeyId(keyCode);
        }

        break;
    }

    case 'M':
    {
        keyId = KeyId::Macro(0);
        
        break;
    }

    case 'L':
    {
        keyId = KeyId::Layer(0);
        
        break;
    }

    }
}

