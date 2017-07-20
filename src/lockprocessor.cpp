#include "lockprocessor.h"

#include "keyevent.h"

void LockProcessor::processKeyEvent(const KeyEvent& event)
{
    const auto& keyId(event.keyId);

    if (keyId.type() == KeyId::Type::kLock)
    {
        if (event.pressed)
        {
            mTapping.processKey(keyId);
        }
    
        auto lockIndex(keyId.value());

        if (lockIndex < mLockSet.size())
        {
            auto& lock(mLockSet[lockIndex]);
            
            lock.processEvent(event,
                              mTapping.count(keyId),
                              mNext);
        }
    }
    else
    {
        if (keyId.type() == KeyId::Type::kKey && !event.pressed)
        {
            for (auto& lock : mLockSet)
            {
                lock.clearTrigger(event, mNext);
            }
        }

        mNext.processKeyEvent(event);
    }
}
