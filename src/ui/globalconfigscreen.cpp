#include "ui/globalconfigscreen.h"

#include "globalconfig.h"
#include "event/screenevent.h"

GlobalConfigScreen::GlobalConfigScreen(Timer&        timer,
                                       GlobalConfig& globalConfig,
                                       EventStage&   next)
    : mGlobalConfig(globalConfig)
    , mTapDelayEntry("Multi Tap Delay", 140, NumberEntryWidget(0, 9999, timer))
    , mRepeatDelayEntry("Key Repeat Delay", 140, NumberEntryWidget(0, 9999, timer))
    , mRepeatRateEntry("Key Repeat Rate", 140, NumberEntryWidget(0, 9999, timer))
    , mHomeScreenTimeout("Home Screen Timeout", 140, NumberEntryWidget(0, 999999, timer))
    , mSaveButton("Save")
    , mItems({{ mTapDelayEntry,
                mRepeatDelayEntry,
                mRepeatRateEntry,
                mHomeScreenTimeout,
                mSaveButton }})
    , mHStackWidget(mItems, true)
    , mNext(next)
{
    mTapDelayEntry.widget.value      = mGlobalConfig.tapDelay;
    mRepeatDelayEntry.widget.value   = mGlobalConfig.keyRepeatDelay;
    mRepeatRateEntry.widget.value    = mGlobalConfig.keyRepeatRate;
    mHomeScreenTimeout.widget.value  = mGlobalConfig.homeScreenTimeout;

    mSaveButton.activated = Action::memFn<GlobalConfigScreen,
                                          &GlobalConfigScreen::onSave>(this);
}

bool GlobalConfigScreen::processEvent(const Event& event)
{
    return mHStackWidget.processEvent(event);
}

Widget& GlobalConfigScreen::rootWidget()
{
    return mHStackWidget;
}

void GlobalConfigScreen::onSave()
{
    mGlobalConfig.tapDelay          = mTapDelayEntry.widget.value;
    mGlobalConfig.keyRepeatDelay    = mRepeatDelayEntry.widget.value;
    mGlobalConfig.keyRepeatRate     = mRepeatRateEntry.widget.value;
    mGlobalConfig.homeScreenTimeout = mHomeScreenTimeout.widget.value;
    
    mNext.processEvent(ScreenEvent::create(ScreenEvent::Type::kHome));
}

