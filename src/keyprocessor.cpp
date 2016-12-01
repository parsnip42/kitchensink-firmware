#include "keyprocessor.h"

#include "kskeyboard.h"
#include "keyboardstate.h"

#include <keylayouts.h>

KeyProcessor::KeyProcessor(KsKeyboard&    keyboard,
                           KeyboardState& keyboardState)
    : mKeyboard(keyboard)
    , mKeyboardState(keyboardState)
    , mEventQueue()
    , mLayerProcessor(keyboard)
    , mModifierProcessor()
    , mMacroProcessor()
{ }

void KeyProcessor::poll()
{
    mKeyboard.poll([&](const KsKeyboard::Event& event)
    {
        auto keyId(mKeyboardState.layerStack.at(event.row, event.column));
        
        mEventQueue.pushBack(KeyEvent(keyId, event.pressed));
    });
}

KeyProcessor::Consumed KeyProcessor::consumeEvent(const KeyEvent& event)
{
    mLayerProcessor.processEvent(mKeyboardState.layerStack,
                                 event,
                                 mEventQueue);

    mMacroProcessor.processEvent(mKeyboardState.macroSet,
                                 event,
                                 mEventQueue);
            
    if (mModifierProcessor.processEvent(mKeyboardState.modifierSet,
                                        event,
                                        mEventQueue))
    {
        return Consumed::kStateChanged;
    }

    return Consumed::kIgnored;
}

