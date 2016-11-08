#include "keyhandler.h"

#include "eventqueue.h"
#include "kskeyboard.h"

KeyHandler::KeyHandler(KsKeyboard& keyboard)
    : mKeyboard(keyboard)
    , mLayerStack()
{
    mLayerStack.setLayer(0, true);
}

void KeyHandler::assignLayer(int index, const Layer& layer)
{
    mLayerStack.assignLayer(index, layer);
}

void KeyHandler::setLayer(int         index,
                          bool        enabled,
                          EventQueue& eventQueue)
{
    if (enabled != mLayerStack.enabled(index))
    {
        if (enabled)
        {
            pressLayer(index, eventQueue);
            mLayerStack.setLayer(index, enabled);

        }
        else
        {
            mLayerStack.setLayer(index, enabled);
            releaseLayer(index, eventQueue);
        }
    }
}

void KeyHandler::poll(EventQueue& eventQueue)
{
    mKeyboard.poll([&](const KsKeyboard::Event& event)
    {
        auto keyId(mLayerStack.at(event.row, event.column));

        eventQueue.pushBack(KeyEvent(keyId,
                                     event.pressed));
    });
}

void KeyHandler::pressLayer(int index, EventQueue& eventQueue)
{
    mKeyboard.pressed([&](const KsKeyboard::Event& event)
    {
        if (mLayerStack.activeLayer(event.row, event.column) < index)
        {
            auto next(mLayerStack.atIndex(index, event.row, event.column));
            
            if (next != KeyId::None)
            {
                auto current(mLayerStack.at(event.row, event.column));
                
                if (current != next)
                {    
                    eventQueue.pushBack(KeyEvent(current,
                                                 false));
                }
            }
        }
    });
}

void KeyHandler::releaseLayer(int index, EventQueue& eventQueue)
{
    mKeyboard.pressed([&](const KsKeyboard::Event& event)
    {
        if (mLayerStack.activeLayer(event.row, event.column) < index)
        {
            auto current(mLayerStack.atIndex(index, event.row, event.column));

            if (current != KeyId::None)
            {
                auto next(mLayerStack.at(event.row, event.column));
                
                if (current != next)
                {    
                    eventQueue.pushBack(KeyEvent(current,
                                                 false));
                }
            }            
        }
    });
}

