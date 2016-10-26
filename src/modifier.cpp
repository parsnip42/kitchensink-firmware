#include "modifier.h"

#include "eventqueue.h"

Modifier::Modifier(const KeyId& keyId)
    : mKeyId(keyId)
    , mLocked(false)
    , mHeld(false)
{ }

bool Modifier::processEvent(const KeyEvent& keyEvent,
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

    return mHeld || mLocked;
}
