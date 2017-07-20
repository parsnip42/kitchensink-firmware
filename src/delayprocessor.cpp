#include "delayprocessor.h"

#include "keyevent.h"
#include "timed.h"

void DelayProcessor::processKeyEvent(const KeyEvent& event)
{
    auto keyId(event.keyId);

    if (keyId.type() == KeyId::Type::kDelay)
    {
        auto pollFunc([&]()
                      {
                
                      });

        Timed(keyId.delayMs(), pollFunc);
    }
    else
    {
        mNext.processKeyEvent(event);
    }
}
