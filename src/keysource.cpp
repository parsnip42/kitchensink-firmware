#include "keysource.h"

#include "kskeyboard.h"
#include "keyboardstate.h"
#include "keylocation.h"

KeySource::KeySource(KsKeyboard& keyboard,
                     LayerStack& layerStack)
    : mKeyboard(keyboard)
    , mLayerStack(layerStack)
    , mLayerMask()
{
    mLayerMask[0] = true;
}

void KeySource::setLayer(int layer, bool enabled)
{
    if (layer > 0 && layer < int(mLayerMask.size()))
    {
        mLayerMask[layer] = enabled;
    }
}

void KeySource::pollKeyEvent(uint32_t       timeMs,
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

        next.processKeyEvent(keyEvent);
    });

    if (currentLayerMask != mLayerMask)
    {
        processLayerChange(currentLayerMask,
                           mLayerMask,
                           next);
    }
}

bool KeySource::anyPressed()
{
    bool pressed(false);
    
    mKeyboard.pressed([&](const KsKeyboard::Event&)
    {
        pressed = true;
    });

    return pressed;
}

void KeySource::processLayerChange(const LayerStack::Mask& currentMask,
                                   const LayerStack::Mask& nextMask,
                                   KeyEventStage&          next)
{
    mKeyboard.pressed([&](const KsKeyboard::Event& event)
    {
        auto currentKey(mLayerStack.at(currentMask,
                                       event.row,
                                       event.column));
        
        auto nextKey(mLayerStack.at(nextMask,
                                    event.row,
                                    event.column));

        if (currentKey != nextKey)
        {
            next.processKeyEvent(KeyEvent(currentKey, false));
            next.processKeyEvent(KeyEvent(nextKey, true));
        }
    });
}
