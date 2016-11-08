#include "modifierprocessor.h"

#include "keyevent.h"

ModifierProcessor::ModifierProcessor(KeyHandler& keyHandler)
    : mKeyHandler(keyHandler)
    , mTapping(500)
{ }

bool ModifierProcessor::processEvent(const KeyEvent& event,
                                     EventQueue&     eventQueue)
{
    const auto& keyId(event.keyId);

    if (event.pressed)
    {
        mTapping.processKey(keyId);
    }
    
    if (keyId.type() == KeyId::Type::kModifier)
    {
        auto& modifier(mModifierSet[keyId.value()]);

        return modifier.processEvent(event,
                                     mTapping.count(keyId),
                                     eventQueue);
    }
    else if (keyId.type() == KeyId::Type::kKey && !event.pressed)
    {
        bool processed(false);
        
        for (auto& modifier : mModifierSet)
        {
            processed |= modifier.clearTrigger(event, eventQueue);
        }

        return processed;
    }
    
    return false;
}
