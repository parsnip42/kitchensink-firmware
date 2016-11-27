#ifndef INCLUDED_KEYPROCESSOR_H
#define INCLUDED_KEYPROCESSOR_H

#include "eventqueue.h"
#include "keydispatcher.h"
#include "macroprocessor.h"
#include "modifierprocessor.h"
#include "profile.h"
#include "timed.h"

class KeyDispatcher;

class KeyProcessor
{
public:
    KeyProcessor(KeyDispatcher& keyDispatcher,
                 Profile&       profile);

public:
    void pushEvent(const KeyEvent& event);
    
    void poll();
    
    template <typename EventCallback>
    void poll(const EventCallback& eventCallback);

    template <typename EventCallback,
              typename StateCallback>
    void poll(const EventCallback& eventCallback,
              const StateCallback& stateCallback);
    
    template <typename Func>
    void delay(const Func& func,
               uint32_t    timeMs);

private:
    enum class Consumed
    {
        kIgnored,
        kStateChanged,
        kConsumed
    };
    
private:
    Consumed consumeEvent(const KeyEvent& event);
    
private:
    KeyDispatcher&    mKeyDispatcher;
    Profile&          mProfile;
    EventQueue        mEventQueue;
    ModifierProcessor mModifierProcessor;
    MacroProcessor    mMacroProcessor;
    
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
void KeyProcessor::poll()
{
    mKeyDispatcher.poll(mEventQueue);
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
    poll();

    if (!mEventQueue.empty())
    {
        auto event(mEventQueue.pop());
        auto consumed(consumeEvent(event));

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
