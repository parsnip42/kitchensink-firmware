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
            const auto& smartKey(mSmartKeys[index]);
        }
    }
    else
    {
        mNext.processKeyEvent(event);
    }
}
