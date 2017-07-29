#include "multiprocessor.h"

#include "keyevent.h"

void MultiProcessor::processKeyEvent(const KeyEvent& event)
{
    if (mReleaseTimer.matches(event))
    {
        mMultiSet[mLast].trigger(mNext);
        return;
    }
    
    const auto& keyId(event.keyId);

    if (keyId.type() == KeyId::Type::kMulti)
    {
        auto multiId(keyId.value());
        
        if (multiId < mMultiSet.size())
        {
            if (event.pressed)
            {
                mReleaseTimer.schedule(400);
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
