#include "keyprocessor.h"

#include "keydispatcher.h"

#include <keylayouts.h>

KeyProcessor::KeyProcessor(KeyDispatcher& keyDispatcher,
                           Profile&       profile)
    : mKeyDispatcher(keyDispatcher)
    , mProfile(profile)
{ }

KeyProcessor::Consumed KeyProcessor::consumeEvent(const KeyEvent& event)
{
    const auto& keyId(event.keyId);

    if (keyId.type() == KeyId::Type::kLayer)
    {
        mKeyDispatcher.setLayer(keyId.value(), event.pressed, mEventQueue);
        
        return Consumed::kConsumed;
    }
    else
    {
        mMacroProcessor.processEvent(mProfile.macroSet,
                                     event,
                                     mEventQueue);
            
        if (mModifierProcessor.processEvent(mProfile.modifierSet,
                                            event,
                                            mEventQueue))
        {
            return Consumed::kStateChanged;
        }
    }

    return Consumed::kIgnored;
}

