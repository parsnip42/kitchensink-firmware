#include "multikeyprocessor.h"

#include "keyevent.h"

void MultiKeyProcessor::processKeyEvent(const KeyEvent& event)
{
    if (mReleaseTimer.matches(event))
    {
        mMultiKeySet[mLast].trigger(mNext);
        return;
    }
    
    const auto& keyId(event.keyId);

    if (keyId.type() == KeyId::Type::kMulti)
    {
        auto multiId(keyId.value());
        
        if (multiId < mMultiKeySet.size())
        {
            if (event.pressed)
            {
                mReleaseTimer.schedule(300);
                mMultiKeySet[multiId].press();
            }
            else
            {
                mMultiKeySet[multiId].release(mNext);
            }
            
            if (multiId != mLast)
            {
                mMultiKeySet[mLast].trigger(mNext);
            }
            
            mLast = multiId;
        }
    }
    else
    {
        mMultiKeySet[mLast].trigger(mNext);
        mNext.processKeyEvent(event);   
    }
}
