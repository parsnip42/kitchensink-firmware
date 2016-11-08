#include "multi.h"

#include "eventqueue.h"

void Multi::processEvent(bool pressed, EventQueue& eventQueue)
{
    for (const auto& keyId : mKeys)
    {
        if (keyId != KeyId::None)
        {
            eventQueue.pushFront(KeyEvent(keyId, pressed));
        }
    }
}
