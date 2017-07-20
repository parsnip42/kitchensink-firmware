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
    
    template <typename EventCallback>
    void poll(const EventCallback& eventCallback);

    template <typename EventCallback,
              typename StateCallback>
    void poll(const EventCallback& eventCallback,
              const StateCallback& stateCallback);

    void delay(uint32_t timeMs);

    template <typename Func>
    void delay(const Func& func,
               uint32_t    timeMs);

    void untilKeyPress();
    
    void untilIdle();

    KeyLocation readKeyLocation();

private:
    enum class Consumed
    {
        kIgnored,
        kStateChanged,
        kConsumed
    };
    
private:
    Consumed consumeEvent(const KeyEvent& event,
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
    LockProcessor  mLockProcessor;
    MultiProcessor mMultiProcessor;
    MacroProcessor mMacroProcessor;
    
private:
    KeyProcessor(const KeyProcessor&) = delete;
    KeyProcessor& operator=(const KeyProcessor&) = delete;
};


inline
void KeyProcessor::pushEvent(const KeyEvent& event)
{
    mEventQueue.pushBack(event);
}

template <typename EventCallback>
inline
void KeyProcessor::poll(const EventCallback& eventCallback)
{
    poll(eventCallback, [](){});
}

template <typename EventCallback,
          typename StateCallback>
inline
void KeyProcessor::poll(const EventCallback& eventCallback,
                        const StateCallback& stateCallback)
{
    auto timeMs(poll());

    if (!mEventQueue.empty())
    {
        auto event(mEventQueue.pop());
        auto consumed(consumeEvent(event, timeMs));

        switch (consumed)
        {
        case Consumed::kIgnored:
            eventCallback(event);
            break;
        
        case Consumed::kStateChanged:
            stateCallback();
            break;

        default:
            break;
        }
    }
}

template <typename Func>
void KeyProcessor::delay(const Func& func,
                         uint32_t    timeMs)
{
    auto pollFunc([&]()
    {
        poll();
    });
    
    Timed(timeMs, func, pollFunc);
}

#endif
