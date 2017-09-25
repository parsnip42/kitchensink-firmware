#include "ui/savesecurescreen.h"

#include "crypto/entropypool.h"
#include "event/screenevent.h"
#include "keyboardstateutil.h"

SaveSecureScreen::SaveSecureScreen(SecureMacroSet& secureMacroSet,
                                   EntropyPool&    entropyPool,
                                   EventStage&     next)
    : mSecureMacroSet(secureMacroSet)
    , mEntropyPool(entropyPool)
    , mStatusLabel("", Justify::kCenter)
    , mNext(next)
{ }

void SaveSecureScreen::screenInit()
{
    if (mEntropyPool.entryCount() >= 2)
    {
        mStatusLabel.text = "Saving";
        mStatusLabel.invalidateWidget();

        KeyboardStateUtil::store(mSecureMacroSet, mEntropyPool);
        
        screenCompleted.fireAction();
    }
    else
    {
        mStatusLabel.text = "Waiting for Entropy Pool";
        mStatusLabel.invalidateWidget();
    }
}

bool SaveSecureScreen::processEvent(const Event& event)
{
    if (mEntropyPool.entryCount() >= 2)
    {
        mStatusLabel.text = "Saving";
        mStatusLabel.invalidateWidget();
        
        KeyboardStateUtil::store(mSecureMacroSet, mEntropyPool);
        
        screenCompleted.fireAction();
    }

    // Consume all incoming events.
    
    return true;
}

Widget& SaveSecureScreen::rootWidget()
{
    return mStatusLabel;
}
