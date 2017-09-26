#include "ui/statusscreen.h"

#include "event/eventstage.h"
#include "eventmanager.h"
#include "hardware/ctrlutil.h"
#include "keyboardstate.h"
#include "storage/storage.h"
#include "types/stroutstream.h"
#include "config.h"

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

StatusScreen::StatusScreen(KeyboardState& keyboardState,
                           EventManager&  eventManager)
    : mKeyboardState(keyboardState)
    , mEventManager(eventManager)
    , mMemoryUsage("Free Memory", 120)
    , mConfigSize("Config Size", 120)
    , mScanRate("Scan Rate", 120)
    , mAllocatedTimers("Allocated Timers", 120)
    , mActiveTimers("Active Timers", 120)
    , mMacroPoolUsage("Macro Pool", 120)
    , mSMacroPoolUsage("Secure Macro Pool", 120)
    , mItems({{ mMemoryUsage,
                mConfigSize,
                mScanRate,
                mAllocatedTimers,
                mActiveTimers,
                mMacroPoolUsage,
                mSMacroPoolUsage }})
    , mHStackWidget(mItems, true)
{ }

bool StatusScreen::processEvent(const Event& event)
{
    return mHStackWidget.processEvent(event);
}

void StatusScreen::screenInit()
{
    {
        StrOutStream os(mMemoryUsage.value);

        os.appendInt(static_cast<int>(CtrlUtil::freeMemory()));
        os.appendStr(" bytes");
        
        mMemoryUsage.invalidateWidget();
    }
    
    {
        StrOutStream os(mConfigSize.value);

        os.appendInt(sizeof(KeyboardState));
        os.appendStr(" bytes");
        
        mConfigSize.invalidateWidget();
    }
    
    {
        StrOutStream os(mAllocatedTimers.value);

        os.appendInt(mEventManager.timer.allocatedTimers());
        os.appendStr(" / ");
        os.appendInt(Config::kTimerCount);
        
        mAllocatedTimers.invalidateWidget();
    }
    
    {
        StrOutStream os(mActiveTimers.value);

        os.appendInt(mEventManager.timer.activeTimers());
        os.appendStr(" / ");
        os.appendInt(Config::kTimerCount);
        
        mActiveTimers.invalidateWidget();
    }

    {
        StrOutStream os(mMacroPoolUsage.value);

        os.appendInt(mKeyboardState.macroSet.poolUsage());
        os.appendStr(" / ");
        os.appendInt(mKeyboardState.macroSet.poolCapacity());

        mMacroPoolUsage.invalidateWidget();
    }
    
    {
        if (mKeyboardState.secureMacroSet.unlocked())
        {
            StrOutStream os(mSMacroPoolUsage.value);
            
            os.appendInt(mKeyboardState.secureMacroSet.poolUsage());
            os.appendStr(" / ");
            os.appendInt(mKeyboardState.secureMacroSet.poolCapacity());
        }
        else
        {
            mSMacroPoolUsage.value = "Locked";
        }
        
        mMacroPoolUsage.invalidateWidget();
    }
    
    mScanRate.invalidateWidget();

    auto start(millis());

    NullKeyStage nullNext;
    
    for (int i(0); i < 100; ++i)
    {
        mEventManager.poll(nullNext);
    }
    
    auto end(millis());

    {
        StrOutStream os(mScanRate.value);
        
        os.appendInt(static_cast<int>((100 * 1000) / (end - start)));
        os.appendStr(" polls/s");

        mScanRate.invalidateWidget();
    }
}

Widget& StatusScreen::rootWidget()
{
    return mHStackWidget;
}
