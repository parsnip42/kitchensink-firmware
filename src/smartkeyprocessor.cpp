#include "smartkeyprocessor.h"

#include "event/event.h"
#include "event/smartevent.h"
#include "event/invalidateevent.h"

SmartKeyProcessor::SmartKeyProcessor(SmartKeySet& smartKeys,
                                     EventStage&  next)
    : mSmartKeys(smartKeys)
    , mNext(next)
{ }

void SmartKeyProcessor::processEvent(const Event& event)
{
    if (event.is<SmartEvent>())
    {
        auto smartEvent(event.get<SmartEvent>());
        auto index(smartEvent.smartId);

        if (index < mSmartKeys.size())
        {
            auto& smartKey(mSmartKeys[index]);

            switch (smartKey.type)
            {
            case SmartKey::Type::kToggle:
            case SmartKey::Type::kToggleAutoRelease:
                if (smartEvent.pressed)
                {
                    mNext.processEvent(!smartKey.enabled ? smartKey.event : smartKey.event.invert());
                    smartKey.enabled = !smartKey.enabled;
                }
                break;

            case SmartKey::Type::kHoldAutoRelease:
                if (smartEvent.pressed != smartKey.enabled)
                {
                    mNext.processEvent(smartEvent.pressed ? smartKey.event : smartKey.event.invert());
                    smartKey.enabled = smartEvent.pressed;
                }
                break;

            case SmartKey::Type::kPair:
                if (smartEvent.pressed)
                {
                    mNext.processEvent(smartKey.event);
                    mNext.processEvent(smartKey.event.invert());
                }
                else
                {
                    mNext.processEvent(smartKey.auxEvent);
                    mNext.processEvent(smartKey.auxEvent.invert());
                }
                break;
                
            case SmartKey::Type::kHoldOrTap:
                if (smartEvent.pressed)
                {
                    mNext.processEvent(smartKey.event);
                    smartKey.enabled = true;
                }
                else
                {
                    mNext.processEvent(smartKey.event.invert());
                    
                    if (smartKey.enabled)
                    {
                        mNext.processEvent(smartKey.auxEvent);
                        mNext.processEvent(smartKey.auxEvent.invert());
                    }
                    
                    smartKey.enabled = false;
                }
                break;

            default:
                break;
            }

            mNext.processEvent(InvalidateEvent::create(InvalidateEvent::Type::kSmartKey,
                                                       index));
        }
    }
    else
    {
        mNext.processEvent(event);
        
        for (size_t index(0); index < mSmartKeys.size(); ++index)
        {
            auto& smartKey(mSmartKeys[index]);
            
            switch (smartKey.type)
            {
            case SmartKey::Type::kToggle:
                if (event == smartKey.event && smartKey.enabled)
                {
                    smartKey.enabled = false;
                    mNext.processEvent(InvalidateEvent::create(InvalidateEvent::Type::kSmartKey,
                                                               index));
                }
                break;
                
            case SmartKey::Type::kToggleAutoRelease:
                if (smartKey.enabled)
                {
                    mNext.processEvent(smartKey.event.invert());
                    smartKey.enabled = false;
                    mNext.processEvent(InvalidateEvent::create(InvalidateEvent::Type::kSmartKey,
                                                               index));
                }
                break;

            case SmartKey::Type::kHoldAutoRelease:
                if (smartKey.enabled)
                {
                    mNext.processEvent(smartKey.event.invert());
                    smartKey.enabled = false;
                    mNext.processEvent(InvalidateEvent::create(InvalidateEvent::Type::kSmartKey,
                                                               index));
                }
                break;

            case SmartKey::Type::kHoldOrTap:
                if (smartKey.enabled)
                {
                    smartKey.enabled = false;
                    mNext.processEvent(InvalidateEvent::create(InvalidateEvent::Type::kSmartKey,
                                                               index));
                }
                break;
                
            default:
                break;
            }
        }
    }
}
