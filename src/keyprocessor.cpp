#include "keyprocessor.h"

#include "kskeyboard.h"
#include "keyboardstate.h"
#include "keylocation.h"

KeyProcessor::KeyProcessor(KsKeyboard& keyboard,
                           LayerStack& layerStack)
    : mKeyboard(keyboard)
    , mLayerStack(layerStack)
    , mLayerMask()
{
    mLayerMask[0] = true;
}

void KeyProcessor::pollKeyEvent(uint32_t       timeMs,
                                KeyEventStage& next)
{
    // Layer changes shouldn't take effect until the next set of key events -
    // take a copy of the mask.
    auto currentLayerMask(mLayerMask);

    mKeyboard.poll(timeMs, [&](const KsKeyboard::Event& event)
    {
        auto keyId(mLayerStack.at(currentLayerMask,
                                  event.row,
                                  event.column));

        auto keyEvent(KeyEvent(keyId, event.pressed));

        if (keyId.type() == KeyId::Type::kLayer)
        {
            mLayerMask[keyId.value()] = event.pressed;
        }
        else
        {
            next.processKeyEvent(keyEvent);
        }
    });

    if (currentLayerMask != mLayerMask)
    {
        processLayerChange(currentLayerMask,
                           mLayerMask,
                           next);
    }
}

void KeyProcessor::pressAll(KeyEventStage& next)
{
    mKeyboard.pressed([&](const KsKeyboard::Event& event)
    {
        auto keyId(mLayerStack.at(mLayerMask,
                                  event.row,
                                  event.column));
        
        auto keyEvent(KeyEvent(keyId, true));
        
        next.processKeyEvent(keyEvent);
    });
}

void KeyProcessor::releaseAll(KeyEventStage& next)
{
    mKeyboard.pressed([&](const KsKeyboard::Event& event)
    {
        auto keyId(mLayerStack.at(mLayerMask,
                                  event.row,
                                  event.column));
        
        auto keyEvent(KeyEvent(keyId, false));

        next.processKeyEvent(keyEvent);
    });
}

void KeyProcessor::processLayerChange(const LayerStack::Mask& currentMask,
                                      const LayerStack::Mask& nextMask,
                                      KeyEventStage&          next)
{
    mKeyboard.pressed([&](const KsKeyboard::Event& event)
    {
        auto currentKey(mLayerStack.at(currentMask, event.row, event.column));
        auto nextKey(mLayerStack.at(nextMask, event.row, event.column));

        if (currentKey != nextKey)
        {
            next.processKeyEvent(KeyEvent(currentKey, false));
            next.processKeyEvent(KeyEvent(nextKey, true));
        }
    });
}
