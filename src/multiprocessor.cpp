#include "multiprocessor.h"

#include "eventqueue.h"
#include "keyevent.h"

bool MultiProcessor::processEvent(const KeyEvent& event,
                                  EventQueue&     eventQueue)
{
    const auto& keyId(event.keyId);

    if (keyId.type() == KeyId::Type::kMulti)
    {
        size_t entry(keyId.value());

        if (entry < 30)
        {
            mMulti[entry].processEvent(event.pressed, eventQueue);
            
            return true;
        }
    }

    return false;
}

void MultiProcessor::assign(int index, const Multi& multi)
{
    mMulti[index] = multi;
}
