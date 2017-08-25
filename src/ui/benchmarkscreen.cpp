#include "ui/benchmarkscreen.h"

#include "eventmanager.h"
#include "hardware/ctrlutil.h"
#include "storage/storage.h"
#include "keyboardstate.h"

#include <elapsedMillis.h>

namespace
{

class NullKeyStage : public EventStage
{
public:
    virtual bool processEvent(const Event& event) override
    {
        return true;
    }
};

}

BenchmarkScreen::BenchmarkScreen(EventManager& eventManager)
    : mEventManager(eventManager)
    , mMemoryUsage("Free Memory", 100)
    , mConfigSize("Config Size", 100)
    , mScanRate("Scan Rate", 100)
    , mItems({ mMemoryUsage, mConfigSize, mScanRate })
    , mHStackWidget(mItems, true)
{ }

bool BenchmarkScreen::processEvent(const Event& event)
{
    return false;
}

void BenchmarkScreen::screenInit()
{
    {
        StrOStream os(mMemoryUsage.value);

        os.appendInt(static_cast<int>(CtrlUtil::freeMemory()));
        os.appendStr(" bytes");
        
        mMemoryUsage.invalidateWidget();
    }
    
    {
        StrOStream os(mConfigSize.value);

        os.appendInt(sizeof(KeyboardState));
        os.appendStr(" bytes");
        
        mConfigSize.invalidateWidget();
    }

    auto start(millis());

    NullKeyStage nullNext;
    
    for (int i(0); i < 500; ++i)
    {
        mEventManager.poll(nullNext);
    }
    
    auto end(millis());

    {
        StrOStream os(mScanRate.value);
        
        os.appendInt(static_cast<int>((500 * 1000) / (end - start)));
        os.appendStr(" polls/s");

        mScanRate.invalidateWidget();
    }
}

Widget& BenchmarkScreen::rootWidget()
{
    return mHStackWidget;
}
