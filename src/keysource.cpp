#include "keysource.h"

#include "event/keyevent.h"
#include "kskeyboard.h"
#include "keyboardstate.h"
#include "keylocation.h"

#include <elapsedMillis.h>

KeySource::KeySource(KsKeyboard& keyboard,
                     LayerStack& nLayerStack)
    : layerStack(nLayerStack)
    , mKeyboard(keyboard)
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

void KeySource::pollEvent(EventStage& next)
{
    auto timeMs(millis());
    
    // Layer changes shouldn't take effect until the next set of key events -
    // take a copy of the mask.
    auto currentLayerMask(mLayerMask);

    mKeyboard.poll(timeMs, KsKeyboard::EventHandler::create([&](const KsKeyboard::Event& keyboardEvent)
    {
        auto event(layerStack.at(currentLayerMask,
                                  keyboardEvent.row,
                                  keyboardEvent.column));

        if (!keyboardEvent.pressed)
        {
            event = event.invert();
        }
        
        if (event != Event())
        {
            next.processEvent(event);
        }
    }));
    
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
    
    mKeyboard.pressed(KsKeyboard::EventHandler::create([&](const KsKeyboard::Event&)
    {
        pressed = true;
    }));

    return pressed;
}

bool KeySource::readKeyLocation(KeyLocation& location)
{
    bool locationSet(false);
    
    mKeyboard.pressed(KsKeyboard::EventHandler::create([&](const KsKeyboard::Event& keyboardEvent)
    {
        location.row    = keyboardEvent.row;
        location.column = keyboardEvent.column;
        locationSet     = true;
    }));
    
    return locationSet;
}

void KeySource::processLayerChange(const LayerStack::Mask& currentMask,
                                   const LayerStack::Mask& nextMask,
                                   EventStage&             next)
{
    mKeyboard.pressed(KsKeyboard::EventHandler::create([&](const KsKeyboard::Event& event)
    {
        auto currentEvent(layerStack.at(currentMask,
                                        event.row,
                                        event.column));
        
        auto nextEvent(layerStack.at(nextMask,
                                     event.row,
                                     event.column));

        if (currentEvent != nextEvent)
        {
            next.processEvent(currentEvent.invert());
            next.processEvent(nextEvent);
        }
    }));
}
