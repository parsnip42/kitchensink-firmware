#include "actionprocessor.h"

#include "crypto/entropypool.h"
#include "event/actionevent.h"
#include "event/event.h"
#include "hardware/ctrlutil.h"
#include "storage/storage.h"
#include "types/dataref.h"

ActionProcessor::ActionProcessor(EntropyPool& entropyPool,
                                 EventStage&  next)
    : mEntropyPool(entropyPool)
    , mNext(next)
{ }

bool ActionProcessor::processEvent(const Event& event)
{
    if (event.is<ActionEvent>())
    {
        auto actionId(event.get<ActionEvent>().actionId);
        
        switch (actionId)
        {
        case 0:
            CtrlUtil::bootloader();
            break;
            
        case 10:
        {
            Storage storage;

            auto os(storage.write(Storage::Region::kEntropyPoolDump));

            os.write(DataRef(mEntropyPool.begin(), mEntropyPool.end()));
            mEntropyPool.clear();
        }
        break;
            
        default:
            break;
        }
    }
    else
    {
        mNext.processEvent(event);
    }

    return true;
}

