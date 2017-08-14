#include "smartkeyprocessor.h"

#include "event/event.h"

SmartKeyProcessor::SmartKeyProcessor(SmartKeySet& smartKeys,
                                     EventStage&  next)
    : mSmartKeys(smartKeys)
    , mNext(next)
{ }

void SmartKeyProcessor::processEvent(const Event& event)
{
    // auto keyId(event.keyId);

    // if (keyId.type() == KeyId::Type::kSmart)
    // {
    //     auto index(keyId.value());

    //     if (index < mSmartKeys.size())
    //     {
    //         auto& smartKey(mSmartKeys[index]);

    //         switch (smartKey.type)
    //         {
    //         case SmartKey::Type::kToggle:
    //         case SmartKey::Type::kToggleAutoRelease:
    //             if (event.pressed)
    //             {
    //                 mNext.processEvent(Event(smartKey.keyId, !smartKey.enabled));
    //                 smartKey.enabled = !smartKey.enabled;
    //             }
    //             break;

    //         case SmartKey::Type::kHoldAutoRelease:
    //             if (event.pressed != smartKey.enabled)
    //             {
    //                 mNext.processEvent(Event(smartKey.keyId, event.pressed));
    //                 smartKey.enabled = event.pressed;
    //             }
    //             break;

    //         case SmartKey::Type::kPair:
    //             if (event.pressed)
    //             {
    //                 mNext.processEvent(Event(smartKey.keyId, true));
    //                 mNext.processEvent(Event(smartKey.keyId, false));
    //             }
    //             else
    //             {
    //                 mNext.processEvent(Event(smartKey.auxKeyId, true));
    //                 mNext.processEvent(Event(smartKey.auxKeyId, false));                    
    //             }
    //             break;
                
    //         case SmartKey::Type::kHoldOrTap:
    //             if (event.pressed)
    //             {
    //                 mNext.processEvent(Event(smartKey.keyId, true));
    //                 smartKey.enabled = true;
    //             }
    //             else
    //             {
    //                 mNext.processEvent(Event(smartKey.keyId, false));
                    
    //                 if (smartKey.enabled)
    //                 {
    //                     mNext.processEvent(Event(smartKey.auxKeyId, true));
    //                     mNext.processEvent(Event(smartKey.auxKeyId, false));                    
    //                 }
                    
    //                 smartKey.enabled = false;
    //             }
    //             break;

    //         default:
    //             break;
    //         }
    //     }
    // }
    // else
    // {
    //     for (auto& smartKey : mSmartKeys)
    //     {
    //         switch (smartKey.type)
    //         {
    //         case SmartKey::Type::kToggle:
    //             if (keyId == smartKey.keyId && smartKey.enabled)
    //             {
    //                 smartKey.enabled = false;
    //             }
    //             break;
                
    //         case SmartKey::Type::kToggleAutoRelease:
    //             if (smartKey.enabled && !event.pressed)
    //             {
    //                 mNext.processEvent(Event(smartKey.keyId, false));
    //                 smartKey.enabled = false;
    //             }
    //             break;

    //         case SmartKey::Type::kHoldAutoRelease:
    //             if (smartKey.enabled && !event.pressed)
    //             {
    //                 mNext.processEvent(Event(smartKey.keyId, false));
    //                 smartKey.enabled = false;
    //             }
    //             break;

    //         case SmartKey::Type::kHoldOrTap:
    //             smartKey.enabled = false;
    //             break;
                
    //         default:
    //             break;
    //         }
    //     }
        
    // }
    
    mNext.processEvent(event);
}
