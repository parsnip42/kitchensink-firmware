#include "keyprocessor.h"

#include "kskeyboard.h"
#include "keyboardstate.h"
#include "keylocation.h"

#include <elapsedMillis.h>

KeyProcessor::KeyProcessor(KsKeyboard&    keyboard,
                           LayerStack&    layerStack,
                           KeyEventStage& next)
    : mKeyboard(keyboard)
    , mLayerStack(layerStack)
    , mNext(next)
{ }

void KeyProcessor::pollKeyEvent(uint32_t timeMs)
{
    mKeyboard.poll(timeMs, [&](const KsKeyboard::Event& event)
    {
        auto keyId(mLayerStack.at(event.row, event.column));

        auto keyEvent(KeyEvent(keyId, event.pressed));
        auto consumed(consumeEvent(keyEvent, timeMs));

        if (!consumed)
        {
            mNext.processKeyEvent(keyEvent);
        }
    });    
}

bool KeyProcessor::consumeEvent(const KeyEvent& event,
                                uint32_t        timeMs)
{
    auto keyId(event.keyId);

    if (keyId.type() == KeyId::Type::kLayer)
    {
        setLayer(keyId.value(),
                 event.pressed);
        
        return true;
    }

    return false;
}

void KeyProcessor::untilKeyPress()
{
}

void KeyProcessor::untilIdle()
{
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
                keyLocation.layer  = mLayerStack.activeLayer(event.row, event.column);
                complete = true;
            }
            
            auto keyId(mLayerStack.at(event.row, event.column));
            
            mEventQueue.pushBack(KeyEvent(keyId, event.pressed));
        });

        while (!mEventQueue.empty())
        {
            consumeEvent(mEventQueue.pop(), timeMs);
        }
    }
    
    return keyLocation;
}

void KeyProcessor::setLayer(int  index,
                            bool enabled)
{
    if (enabled != mLayerStack.enabled(index))
    {
        if (enabled)
        {
            pressLayer(index);
            mLayerStack.setLayer(index, enabled);

        }
        else
        {
            mLayerStack.setLayer(index, enabled);
            releaseLayer(index);
        }
    }
}

void KeyProcessor::pressLayer(int index)
{
    mKeyboard.pressed([&](const KsKeyboard::Event& event)
    {
        if (mLayerStack.activeLayer(event.row, event.column) < index)
        {
            auto next(mLayerStack.atIndex(index, event.row, event.column));
            
            if (next != KeyId())
            {
                auto current(mLayerStack.at(event.row, event.column));
                
                if (current != next)
                {    
                    mEventQueue.pushBack(KeyEvent(current, false));
                    mEventQueue.pushBack(KeyEvent(next, true));
                }
            }
        }
    });
}

void KeyProcessor::releaseLayer(int index)
{
    mKeyboard.pressed([&](const KsKeyboard::Event& event)
    {
        if (mLayerStack.activeLayer(event.row, event.column) < index)
        {
            auto current(mLayerStack.atIndex(index, event.row, event.column));

            if (current != KeyId())
            {
                auto next(mLayerStack.at(event.row, event.column));
                
                if (current != next)
                {    
                    mEventQueue.pushBack(KeyEvent(current, false));
                    mEventQueue.pushBack(KeyEvent(next, true));
                }
            }            
        }
    });
}
