#include "modifierprocessor.h"

#include "keyevent.h"

bool ModifierProcessor::processEvent(ModifierSet&    modifierSet,
                                     const KeyEvent& event,
                                     EventQueue&     eventQueue)
{
    const auto& keyId(event.keyId);

    if (keyId.type() == KeyId::Type::kModifier)
    {
        if (event.pressed)
        {
            mTapping.processKey(keyId);
        }
    
        auto modifierIndex(keyId.value());

        if (modifierIndex < modifierSet.size())
        {
            auto& modifier(modifierSet[modifierIndex]);
            
            return modifier.processEvent(event,
                                         mTapping.count(keyId),
                                         eventQueue);
        }
    }
    else if (keyId.type() == KeyId::Type::kKey && !event.pressed)
    {
        for (auto& modifier : modifierSet)
        {
            modifier.clearTrigger(event, eventQueue);
        }
    }
    
    return false;
}
