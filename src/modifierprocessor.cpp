#include "modifierprocessor.h"

#include "keyevent.h"

ModifierProcessor::ModifierProcessor(KeyHandler& keyHandler)
    : mKeyHandler(keyHandler)
{ }

bool ModifierProcessor::processEvent(const KeyEvent& event,
                                     EventQueue&     eventQueue)
{
    const auto& keyId(event.keyId);
    
    if (keyId.type() == KeyId::kLayer)
    {
        auto& modifier(mLayers[keyId.value()]);
        
        mKeyHandler.setLayer(keyId.value(),
                             modifier.processEvent(event),
                             eventQueue);
    }
    
    return false;
}
