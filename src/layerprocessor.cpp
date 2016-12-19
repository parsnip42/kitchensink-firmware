#include "layerprocessor.h"

#include "eventqueue.h"
#include "keyevent.h"
#include "kskeyboard.h"
#include "layerstack.h"

bool LayerProcessor::processEvent(LayerStack&     layerStack,
                                  const KeyEvent& event,
                                  EventQueue&     eventQueue)
{
    auto keyId(event.keyId);
    
    if (keyId.type() == KeyId::Type::kLayer)
    {
        setLayer(layerStack,
                 keyId.value(),
                 event.pressed,
                 eventQueue);
        
        return true;
    }
    
    return false;
}

void LayerProcessor::setLayer(LayerStack& layerStack,
                          int         index,
                          bool        enabled,
                          EventQueue& eventQueue)
{
    if (enabled != layerStack.enabled(index))
    {
        if (enabled)
        {
            pressLayer(layerStack, index, eventQueue);
            layerStack.setLayer(index, enabled);

        }
        else
        {
            layerStack.setLayer(index, enabled);
            releaseLayer(layerStack, index, eventQueue);
        }
    }
}

void LayerProcessor::pressLayer(LayerStack& layerStack,
                                int         index,
                                EventQueue& eventQueue)
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
                    eventQueue.pushBack(KeyEvent(current,
                                                 false));
                }
            }
        }
    });
}

void LayerProcessor::releaseLayer(LayerStack& layerStack,
                                  int         index,
                                  EventQueue& eventQueue)
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
                    eventQueue.pushBack(KeyEvent(current,
                                                 false));
                }
            }            
        }
    });
}

