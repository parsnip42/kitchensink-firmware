#ifndef INCLUDED_KEYPROCESSOR_H
#define INCLUDED_KEYPROCESSOR_H

#include "eventqueue.h"
#include "macroprocessor.h"
#include "multiprocessor.h"
#include "lockprocessor.h"
#include "timed.h"

class KsKeyboard;
class KeyboardState;
class KeyLocation;
class LayerStack;

class KeyProcessor
{
public:
    KeyProcessor(KsKeyboard&    keyboard,
                 KeyboardState& keyboardState);

public:
    void pushEvent(const KeyEvent& event);
    
    uint32_t poll();
    
    uint32_t poll(KeyEventStage& stage);

    void untilKeyPress();
    
    void untilIdle();

    KeyLocation readKeyLocation();

private:
    bool consumeEvent(const KeyEvent& event,
                      uint32_t        timeMs);
    
    void setLayer(LayerStack& layerStack,
                  int         index,
                  bool        enabled);

    void pressLayer(LayerStack& layerStack,
                    int         index);

    void releaseLayer(LayerStack& layerStack,
                      int         index);

private:
    KsKeyboard&    mKeyboard;
    KeyboardState& mKeyboardState;
    EventQueue     mEventQueue;
    
private:
    KeyProcessor(const KeyProcessor&) = delete;
    KeyProcessor& operator=(const KeyProcessor&) = delete;
};


inline
void KeyProcessor::pushEvent(const KeyEvent& event)
{
    mEventQueue.pushBack(event);
}

inline
uint32_t KeyProcessor::poll(KeyEventStage& stage)
{
    auto timeMs(poll());

    if (!mEventQueue.empty())
    {
        auto event(mEventQueue.pop());
        auto consumed(consumeEvent(event, timeMs));

        if (!consumed)
        {
            stage.processKeyEvent(event);
        }
    }

    return timeMs;
}

#endif
