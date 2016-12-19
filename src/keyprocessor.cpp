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
    , mLockProcessor()
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

void KeyProcessor::delay(uint32_t timeMs)
{
    auto pollFunc([&]()
    {
        poll();
    });
    
    Timed(timeMs, pollFunc);
}

KeyProcessor::Consumed KeyProcessor::consumeEvent(const KeyEvent& event)
{
    auto keyId(event.keyId);

    if (keyId.type() == KeyId::Type::kDelay)
    {
        delay((keyId.subType()) << 8 | (keyId.value()));
    }

    if (mLayerProcessor.processEvent(mKeyboardState.layerStack,
                                     event,
                                     mEventQueue))
    {
        return Consumed::kStateChanged;
    }

    if (mLockProcessor.processEvent(mKeyboardState.lockSet,
                                    event,
                                    mEventQueue))
    {
        return Consumed::kStateChanged;
    }
    
    mMacroProcessor.processEvent(mKeyboardState.macroSet,
                                 event,
                                 mEventQueue);
            

    return Consumed::kIgnored;
}

void KeyProcessor::untilKeyPress()
{
    while (true)
    {
        poll();

        if (!mEventQueue.empty())
        {
            auto event(mEventQueue.pop());

            if (event.pressed)
            {
                break;
            }
        }
    }
};
