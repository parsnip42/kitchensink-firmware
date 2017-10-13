#include "keysource.h"

#include "event/keyevent.h"
#include "kskeyboard.h"
#include "keyboardstate.h"
#include "keylocation.h"
#include "hardware/ctrlutil.h"

KeySource::KeySource(KeyHardware& keyHardware,
                     LayerStack&  layerStack)
    : mKeyHardware(keyHardware)
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

void KeySource::pollEvent(EventStage& next)
{
    auto timeMs(CtrlUtil::nowMs());
    
    // Layer changes shouldn't take effect until the next set of key events -
    // take a copy of the mask.
    auto currentLayerMask(mLayerMask);

    mKeyHardware.poll(timeMs, KeyHardwareEventHandler::create([&](const KeyHardwareEvent& keyboardEvent)
    {
        auto event(mLayerStack.at(currentLayerMask,
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
    
    mKeyHardware.pressed(KeyHardwareEventHandler::create([&](const KeyHardwareEvent&)
    {
        pressed = true;
    }));

    return pressed;
}

bool KeySource::readKeyLocation(KeyLocation& location)
{
    bool locationSet(false);
    
    mKeyHardware.pressed(KeyHardwareEventHandler::create([&](const KeyHardwareEvent& keyboardEvent)
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
    mKeyHardware.pressed(KeyHardwareEventHandler::create([&](const KeyHardwareEvent& event)
    {
        auto currentEvent(mLayerStack.at(currentMask,
                                        event.row,
                                        event.column));
        
        auto nextEvent(mLayerStack.at(nextMask,
                                     event.row,
                                     event.column));

        if (currentEvent != nextEvent)
        {
            next.processEvent(currentEvent.invert());
            next.processEvent(nextEvent);
        }
    }));
}
