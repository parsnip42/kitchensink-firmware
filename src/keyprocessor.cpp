#include "keyprocessor.h"

#include "kskeyboard.h"
#include "keyboardstate.h"
#include "keylocation.h"

KeyProcessor::KeyProcessor(KsKeyboard&    keyboard,
                           LayerStack&    layerStack)
    : mKeyboard(keyboard)
    , mLayerStack(layerStack)
{ }

void KeyProcessor::pollKeyEvent(uint32_t       timeMs,
                                KeyEventStage& next)
{
    mKeyboard.poll(timeMs, [&](const KsKeyboard::Event& event)
    {
        auto keyId(mLayerStack.at(event.row, event.column));

        auto keyEvent(KeyEvent(keyId, event.pressed));

        if (keyId.type() == KeyId::Type::kLayer)
        {
            setLayer(keyId.value(),
                     event.pressed,
                     next);
        }
        else
        {
            next.processKeyEvent(keyEvent);
        }
    });
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

    // bool complete(false);

    // while (!complete)
    // {
    //     auto timeMs(millis());

    //     mKeyboard.poll(timeMs,
    //                    [&](const KsKeyboard::Event& event)
    //     {
    //         if (event.pressed)
    //         {
    //             keyLocation.row    = event.row;
    //             keyLocation.column = event.column;
    //             keyLocation.layer  = mLayerStack.activeLayer(event.row, event.column);
    //             complete = true;
    //         }
            
    //         auto keyId(mLayerStack.at(event.row, event.column));
            
    //         mEventQueue.pushBack(KeyEvent(keyId, event.pressed));
    //     });

    //     while (!mEventQueue.empty())
    //     {
    //         consumeEvent(mEventQueue.pop(), timeMs);
    //     }
    // }
    
    return keyLocation;
}

void KeyProcessor::pressAll(KeyEventStage& next)
{
    mKeyboard.pressed([&](const KsKeyboard::Event& event)
    {
        auto keyId(mLayerStack.at(event.row, event.column));
        auto keyEvent(KeyEvent(keyId, true));
        
        next.processKeyEvent(keyEvent);
    });
}

void KeyProcessor::releaseAll(KeyEventStage& next)
{
    mKeyboard.pressed([&](const KsKeyboard::Event& event)
    {
        auto keyId(mLayerStack.at(event.row, event.column));
        auto keyEvent(KeyEvent(keyId, false));

        next.processKeyEvent(keyEvent);
    });
}

void KeyProcessor::setLayer(int            index,
                            bool           enabled,
                            KeyEventStage& next)
{
    if (enabled != mLayerStack.enabled(index))
    {
        if (enabled)
        {
            pressLayer(index, next);
            mLayerStack.setLayer(index, enabled);

        }
        else
        {
            mLayerStack.setLayer(index, enabled);
            releaseLayer(index, next);
        }
    }
}

void KeyProcessor::pressLayer(int            index,
                              KeyEventStage& next)
{
    mKeyboard.pressed([&](const KsKeyboard::Event& event)
    {
        if (mLayerStack.activeLayer(event.row, event.column) < index)
        {
            auto nextKey(mLayerStack.atIndex(index, event.row, event.column));
            
            if (nextKey != KeyId())
            {
                auto current(mLayerStack.at(event.row, event.column));
                
                if (current != nextKey)
                {    
                    next.processKeyEvent(KeyEvent(current, false));
                    // next.processKeyEvent(KeyEvent(nextKey, true));
                }
            }
        }
    });
}

void KeyProcessor::releaseLayer(int          index,
                                KeyEventStage& next)
{
    mKeyboard.pressed([&](const KsKeyboard::Event& event)
    {
        if (mLayerStack.activeLayer(event.row, event.column) < index)
        {
            auto current(mLayerStack.atIndex(index, event.row, event.column));

            if (current != KeyId())
            {
                auto nextKey(mLayerStack.at(event.row, event.column));
                
                if (current != nextKey)
                {    
                    next.processKeyEvent(KeyEvent(current, false));
                    // next.processKeyEvent(KeyEvent(nextKey, true));
                }
            }            
        }
    });
}
