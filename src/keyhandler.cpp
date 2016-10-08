#include "keyhandler.h"

#include "kskeyboard.h"

KeyHandler::KeyHandler(KsKeyboard& keyboard)
    : mKeyboard(keyboard)
    , mLayerStack()
    , mTapping(250)
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

bool KeyHandler::layerEnabled(int index) const
{
    return mLayerStack.enabled(index);
}

void KeyHandler::poll(EventQueue& eventQueue)
{
    mKeyboard.poll([&](const KsKeyboard::Event& event)
    {
        auto keyId(mLayerStack.at(event.row, event.column));

        if (event.state == KeyState::kPressed)
        {
            mTapping.processKey(keyId);
        }
        
        eventQueue.pushBack(KeyEvent(keyId,
                                     event.state,
                                     mTapping.count(keyId)));
    });
}

void KeyHandler::pressLayer(int index, EventQueue& eventQueue)
{
    mKeyboard.pressed([&](const KsKeyboard::Event& event)
    {
        if (mLayerStack.activeLayer(event.row, event.column) < index)
        {
            auto next(mLayerStack.atIndex(index, event.row, event.column));
            
            if (next.type() != 0)
            {
                auto current(mLayerStack.at(event.row, event.column));
                
                if (current != next)
                {    
                    eventQueue.pushBack(KeyEvent(current,
                                                 KeyState::kReleased,
                                                 0));
                    eventQueue.pushBack(KeyEvent(next,
                                                 KeyState::kPressed,
                                                 0));
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

            if (current.type() != 0)
            {
                auto next(mLayerStack.at(event.row, event.column));
                
                if (current != next)
                {    
                    eventQueue.pushBack(KeyEvent(current,
                                                 KeyState::kReleased,
                                                 0));
                    eventQueue.pushBack(KeyEvent(next,
                                                 KeyState::kPressed,
                                                 0));
                }
            }            
        }
    });
}

