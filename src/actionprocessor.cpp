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
        auto type(event.get<ActionEvent>().type);
        
        switch (type)
        {
        case ActionEvent::Type::Bootloader:
            CtrlUtil::bootloader();
            break;
            
        case ActionEvent::Type::DumpEntropyPool:
        {
            Storage storage;

            auto os(storage.write(Storage::Region::kEntropyPoolDump));

            os.write(DataRef(mEntropyPool.begin(), mEntropyPool.end()));
            mEntropyPool.clear();
            break;
        }
        }
    }
    else
    {
        mNext.processEvent(event);
    }

    return true;
}

