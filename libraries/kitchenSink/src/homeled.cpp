#include "homeled.h"

StrRef HomeLed::text(const SmartKeySet& smartKeySet) const
{
    switch (type)
    {
    case HomeLed::Type::kNone:
        return "None";
        
    case HomeLed::Type::kKeyboard:
        switch (index)
        {
        case HomeLed::kNumLock:
            return "Num Lock";
                
        case HomeLed::kCapsLock:
            return "Caps Lock";
           
        case HomeLed::kScrollLock:
            return "Scroll Lock";

        default:
            break;
        }
         break;

    case HomeLed::Type::kSmartKey:
        if (index < smartKeySet.size())
        {
            return smartKeySet[index].name;
        }
        break;

    default:
        break;
    }

    return "Unknown";
}
