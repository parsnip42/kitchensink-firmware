#include "multi.h"

#include "eventqueue.h"

Multi::Multi(const KeyId& key0,
             const KeyId& key1,
             const KeyId& key2,
             const KeyId& key3)
    : mKeys{{ key0, key1, key2, key3 }}
{ }

void Multi::processEvent(bool pressed, EventQueue& eventQueue)
{
    for (const auto& keyId : mKeys)
    {
        if (keyId != KeyId::None)
        {
            eventQueue.pushBack(KeyEvent(keyId, pressed));
        }
    }
}
