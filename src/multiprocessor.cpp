#include "multiprocessor.h"

#include "eventqueue.h"
#include "keyevent.h"

void MultiProcessor::tick(MultiSet&   multiSet,
                          uint32_t    timeMs,
                          EventQueue& eventQueue)
{
    if (timeMs >= mTapTime + 1000)
    {
        multiSet[mLast].trigger(eventQueue);
    }
}   

bool MultiProcessor::processEvent(MultiSet&       multiSet,
                                  const KeyEvent& event,
                                  uint32_t        timeMs,
                                  EventQueue&     eventQueue)
{
    const auto& keyId(event.keyId);

    if (keyId.type() == KeyId::Type::kMulti)
    {
        auto multiId(keyId.value());
        
        if (multiId < multiSet.size())
        {
            if (event.pressed)
            {
                mTapTime = timeMs;
                multiSet[multiId].press();
            }
            else
            {
                multiSet[multiId].release(eventQueue);
            }
            
            if (multiId != mLast)
            {
                multiSet[mLast].trigger(eventQueue);
            }
            
            mLast = multiId;
        }
        
        return true;
    }
    else
    {
        return multiSet[mLast].trigger(event, eventQueue);
    }

    return false;
}
