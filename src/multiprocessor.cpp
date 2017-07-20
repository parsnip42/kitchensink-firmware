#include "multiprocessor.h"

#include "eventqueue.h"
#include "keyevent.h"

#include <elapsedMillis.h>

void MultiProcessor::tick(uint32_t timeMs)
{
    if (timeMs >= mTapTime + 200)
    {
        mMultiSet[mLast].trigger(mNext);
    }
}   

void MultiProcessor::processKeyEvent(const KeyEvent& event)
{
    auto timeMs(millis());

    const auto& keyId(event.keyId);

    if (keyId.type() == KeyId::Type::kMulti)
    {
        auto multiId(keyId.value());
        
        if (multiId < mMultiSet.size())
        {
            if (event.pressed)
            {
                mTapTime = timeMs;
                mMultiSet[multiId].press();
            }
            else
            {
                mMultiSet[multiId].release(mNext);
            }
            
            if (multiId != mLast)
            {
                mMultiSet[mLast].trigger(mNext);
            }
            
            mLast = multiId;
        }
    }
    else
    {
        mMultiSet[mLast].trigger(mNext);
        mNext.processKeyEvent(event);   
    }
}
