#include "modifier.h"

#include "eventqueue.h"

Modifier::Modifier(const char*  name,
                   const KeyId& keyId)
    : mName(name)
    , mKeyId(keyId)
    , mLocked(false)
    , mHeld(false)
{ }

void Modifier::processEvent(const KeyEvent& keyEvent,
                            EventQueue&     eventQueue)
{
    const auto& keyId(keyEvent.keyId);
    const auto& pressed(keyEvent.pressed);
    
    switch (keyId.modifierType())
    {
    case KeyId::ModifierType::kToggle:
        if (pressed)
        {
            mLocked = !mLocked;
        }
        break;

    default:
        mHeld = pressed;
        break;

    }

    eventQueue.pushBack(KeyEvent(mKeyId, active()));
}
