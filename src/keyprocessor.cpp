#include "keyprocessor.h"

#include "kskeyboard.h"
#include "keyboardstate.h"
#include "keylocation.h"

#include <elapsedMillis.h>

KeyProcessor::KeyProcessor(KsKeyboard&    keyboard,
                           KeyboardState& keyboardState)
    : mKeyboard(keyboard)
    , mKeyboardState(keyboardState)
    , mEventQueue()
    , mLockProcessor()
    , mMacroProcessor()
{ }

uint32_t KeyProcessor::poll()
{
    auto timeMs(millis());
    
    mKeyboard.poll(timeMs, [&](const KsKeyboard::Event& event)
    {
        auto keyId(mKeyboardState.layerStack.at(event.row, event.column));
        
        mEventQueue.pushBack(KeyEvent(keyId, event.pressed));
    });

    mMultiProcessor.tick(mKeyboardState.multiSet,
                         timeMs,
                         mEventQueue);
        
    return timeMs;
}

void KeyProcessor::delay(uint32_t timeMs)
{
    auto pollFunc([&]()
    {
        poll();
    });
    
    Timed(timeMs, pollFunc);
}

KeyProcessor::Consumed KeyProcessor::consumeEvent(const KeyEvent& event,
                                                  uint32_t        timeMs)
{
    auto keyId(event.keyId);

    if (keyId.type() == KeyId::Type::kDelay)
    {
        delay(keyId.delayMs());
    }
    else if (keyId.type() == KeyId::Type::kLayer)
    {
        setLayer(mKeyboardState.layerStack,
                 keyId.value(),
                 event.pressed);
        
        return Consumed::kStateChanged;
    }
    
    if (mLockProcessor.processEvent(mKeyboardState.lockSet,
                                    event,
                                    mEventQueue))
    {
        return Consumed::kStateChanged;
    }

    if (mMultiProcessor.processEvent(mKeyboardState.multiSet,
                                     event,
                                     timeMs,
                                     mEventQueue))
    {
        return Consumed::kConsumed;
    }
    
    if (mMacroProcessor.processEvent(mKeyboardState.macroSet,
                                     event,
                                     mEventQueue))
    {
        return Consumed::kConsumed;
    }

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
}

void KeyProcessor::untilIdle()
{
    while (true)
    {
        poll();
        
        if (!mEventQueue.empty())
        {
            mEventQueue.pop();
        }
        else if (!mKeyboard.any())
        {
            break;
        }
    }
}

KeyLocation KeyProcessor::readKeyLocation()
{
    KeyLocation keyLocation;

    bool complete(false);

    while (!complete)
    {
        auto timeMs(millis());

        mKeyboard.poll(timeMs,
                       [&](const KsKeyboard::Event& event)
        {
            if (event.pressed)
            {
                keyLocation.row    = event.row;
                keyLocation.column = event.column;
                keyLocation.layer  = mKeyboardState.layerStack.activeLayer(event.row, event.column);
                complete = true;
            }
            
            auto keyId(mKeyboardState.layerStack.at(event.row, event.column));
            
            mEventQueue.pushBack(KeyEvent(keyId, event.pressed));
        });

        while (!mEventQueue.empty())
        {
            consumeEvent(mEventQueue.pop(), timeMs);
        }
    }
    
    return keyLocation;
}

void KeyProcessor::setLayer(LayerStack& layerStack,
                            int         index,
                            bool        enabled)
{
    if (enabled != layerStack.enabled(index))
    {
        if (enabled)
        {
            pressLayer(layerStack, index);
            layerStack.setLayer(index, enabled);

        }
        else
        {
            layerStack.setLayer(index, enabled);
            releaseLayer(layerStack, index);
        }
    }
}

void KeyProcessor::pressLayer(LayerStack& layerStack,
                              int         index)
{
    mKeyboard.pressed([&](const KsKeyboard::Event& event)
    {
        if (layerStack.activeLayer(event.row, event.column) < index)
        {
            auto next(layerStack.atIndex(index, event.row, event.column));
            
            if (next != KeyId())
            {
                auto current(layerStack.at(event.row, event.column));
                
                if (current != next)
                {    
                    mEventQueue.pushBack(KeyEvent(current, false));
                    mEventQueue.pushBack(KeyEvent(next, true));
                }
            }
        }
    });
}

void KeyProcessor::releaseLayer(LayerStack& layerStack,
                                int         index)
{
    mKeyboard.pressed([&](const KsKeyboard::Event& event)
    {
        if (layerStack.activeLayer(event.row, event.column) < index)
        {
            auto current(layerStack.atIndex(index, event.row, event.column));

            if (current != KeyId())
            {
                auto next(layerStack.at(event.row, event.column));
                
                if (current != next)
                {    
                    mEventQueue.pushBack(KeyEvent(current, false));
                    mEventQueue.pushBack(KeyEvent(next, true));
                }
            }            
        }
    });
}
