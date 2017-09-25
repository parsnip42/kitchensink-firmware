#include "actionprocessor.h"

#include "crypto/entropypool.h"
#include "event/actionevent.h"
#include "event/event.h"
#include "hardware/ctrlutil.h"
#include "storage/storage.h"
#include "types/dataref.h"
#include "keyboardstate.h"

ActionProcessor::ActionProcessor(KeyboardState& keyboardState,
                                 EntropyPool&   entropyPool,
                                 EventStage&    next)
    : mKeyboardState(keyboardState)
    , mEntropyPool(entropyPool)
    , mNext(next)
{ }

bool ActionProcessor::processEvent(const Event& event)
{
    if (event.is<ActionEvent>())
    {
        auto type(event.get<ActionEvent>().type);
        
        switch (type)
        {
        case ActionEvent::Type::kBootloader:
            CtrlUtil::bootloader();
            break;
            
        case ActionEvent::Type::kDumpEntropyPool:
        {
            Storage storage;

            auto os(storage.write(Storage::Region::kEntropyPoolDump));

            os.write(DataRef(mEntropyPool.begin(), mEntropyPool.end()));
            mEntropyPool.clear();
            break;
        }

        case ActionEvent::Type::kLockSecureMacros:
            mKeyboardState.secureMacroSet.lock();
            break;
        }
    }
    else
    {
        mNext.processEvent(event);
    }

    return true;
}

