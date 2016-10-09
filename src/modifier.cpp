#include "modifier.h"

Modifier::Modifier()
    : mState(false)
    , mSingleTrigger(false)
{ }

bool Modifier::processEvent(const KeyEvent& keyEvent)
{
    const auto& keyId(keyEvent.keyId);
    const auto& keyState(keyEvent.state);
    
    switch (keyId.modifierType())
    {
    case KeyId::ModifierType::kToggle:
        if (keyState == KeyState::kPressed)
        {
            mState = !mState;
        }
        break;

    default:
        if (keyState == KeyState::kPressed)
        {
            mState = true;
        }
        else if (keyState == KeyState::kReleased)
        {
            mState = false;
        }
        break;

    }

    return mState;
}
