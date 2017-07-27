#include "smartkeyprocessor.h"

#include "keyevent.h"

SmartKeyProcessor::SmartKeyProcessor(SmartKeySet&   smartKeys,
                                     KeyEventStage& next)
    : mSmartKeys(smartKeys)
    , mNext(next)
{ }

void SmartKeyProcessor::processKeyEvent(const KeyEvent& event)
{
    auto keyId(event.keyId);

    if (keyId.type() == KeyId::Type::kSmart)
    {
        auto index(keyId.value());

        if (index < mSmartKeys.size())
        {
            auto& smartKey(mSmartKeys[index]);

            switch (smartKey.type)
            {
            case SmartKey::Type::kToggle:
            case SmartKey::Type::kToggleAutoRelease:
                if (event.pressed)
                {
                    mNext.processKeyEvent(KeyEvent(smartKey.keyId, !smartKey.triggered));
                    smartKey.triggered = !smartKey.triggered;
                }
                break;

            case SmartKey::Type::kHoldAutoRelease:
                if (event.pressed != smartKey.triggered)
                {
                    mNext.processKeyEvent(KeyEvent(smartKey.keyId, event.pressed));
                    smartKey.triggered = event.pressed;
                }
                break;

            case SmartKey::Type::kPair:
                if (event.pressed)
                {
                    mNext.processKeyEvent(KeyEvent(smartKey.keyId, true));
                    mNext.processKeyEvent(KeyEvent(smartKey.keyId, false));
                }
                else
                {
                    mNext.processKeyEvent(KeyEvent(smartKey.auxKeyId, true));
                    mNext.processKeyEvent(KeyEvent(smartKey.auxKeyId, false));                    
                }
                break;
                
            case SmartKey::Type::kHoldOrTap:
                if (event.pressed)
                {
                    mNext.processKeyEvent(KeyEvent(smartKey.keyId, true));
                    smartKey.triggered = true;
                }
                else
                {
                    mNext.processKeyEvent(KeyEvent(smartKey.keyId, false));
                    
                    if (smartKey.triggered)
                    {
                        mNext.processKeyEvent(KeyEvent(smartKey.auxKeyId, true));
                        mNext.processKeyEvent(KeyEvent(smartKey.auxKeyId, false));                    
                    }
                    
                    smartKey.triggered = false;
                }
                break;

            default:
                break;
            }
        }
    }
    else
    {
        for (auto& smartKey : mSmartKeys)
        {
            switch (smartKey.type)
            {
            case SmartKey::Type::kToggle:
                if (keyId == smartKey.keyId && smartKey.triggered)
                {
                    smartKey.triggered = false;
                }
                break;
                
            case SmartKey::Type::kToggleAutoRelease:
                if (smartKey.triggered && !event.pressed)
                {
                    mNext.processKeyEvent(KeyEvent(smartKey.keyId, false));
                    smartKey.triggered = false;
                }
                break;

            case SmartKey::Type::kHoldAutoRelease:
                if (smartKey.triggered && !event.pressed)
                {
                    mNext.processKeyEvent(KeyEvent(smartKey.keyId, false));
                    smartKey.triggered = false;
                }
                break;

            case SmartKey::Type::kHoldOrTap:
                smartKey.triggered = false;
                break;
                
            default:
                break;
            }
        }
        
        mNext.processKeyEvent(event);
    }
}
