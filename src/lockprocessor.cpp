#include "lockprocessor.h"

#include "keyevent.h"

bool LockProcessor::processEvent(LockSet&        lockSet,
                                 const KeyEvent& event,
                                 EventQueue&     eventQueue)
{
    const auto& keyId(event.keyId);

    if (keyId.type() == KeyId::Type::kLock)
    {
        if (event.pressed)
        {
            mTapping.processKey(keyId);
        }
    
        auto lockIndex(keyId.value());

        if (lockIndex < lockSet.size())
        {
            auto& lock(lockSet[lockIndex]);
            
            return lock.processEvent(event,
                                     mTapping.count(keyId),
                                     eventQueue);
        }
    }
    else if (keyId.type() == KeyId::Type::kKey && !event.pressed)
    {
        for (auto& lock : lockSet)
        {
            lock.clearTrigger(event, eventQueue);
        }
    }
    
    return false;
}
