#include "modifierprocessor.h"

#include "keyevent.h"

ModifierProcessor::ModifierProcessor(KeyHandler& keyHandler)
    : mKeyHandler(keyHandler)
{ }

bool ModifierProcessor::processEvent(const KeyEvent& event,
                                     EventQueue&     eventQueue)
{
    const auto& keyId(event.keyId);
    
    if (keyId.type() == KeyId::kModifier)
    {
        auto& modifier(mModifierSet[keyId.value()]);

        modifier.processEvent(event, eventQueue);

        return true;
    }
    
    return false;
}
