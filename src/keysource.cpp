#include "keysource.h"

#include "event/keyevent.h"
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

int KeySource::topLayer()
{
    for (int layer(mLayerMask.size() - 1); layer >= 0; --layer)
    {
        if (mLayerMask[layer])
        {
            return layer;
        }
    }

    return -1;
}

void KeySource::pollEvent(uint32_t    timeMs,
                          EventStage& next)
{
    // Layer changes shouldn't take effect until the next set of key events -
    // take a copy of the mask.
    auto currentLayerMask(mLayerMask);

    mKeyboard.poll(timeMs, [&](const KsKeyboard::Event& keyboardEvent)
    {
        auto event(mLayerStack.at(currentLayerMask,
                                  keyboardEvent.row,
                                  keyboardEvent.column));

        if (!keyboardEvent.pressed)
        {
            event = event.invert();
        }
        
        next.processEvent(event);
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
                                   EventStage&          next)
{
    mKeyboard.pressed([&](const KsKeyboard::Event& event)
    {
        auto currentEvent(mLayerStack.at(currentMask,
                                       event.row,
                                       event.column));
        
        auto nextEvent(mLayerStack.at(nextMask,
                                    event.row,
                                    event.column));

        if (currentEvent != nextEvent)
        {
            // next.processEvent(Event(currentKey, false));
            // next.processEvent(Event(nextKey, true));
        }
    });
}
