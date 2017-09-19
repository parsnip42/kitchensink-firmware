#include "ui/globalconfigscreen.h"

#include "globalconfig.h"
#include "event/screenevent.h"

GlobalConfigScreen::GlobalConfigScreen(Timer&        timer,
                                       GlobalConfig& globalConfig,
                                       EventStage&   next)
    : mGlobalConfig(globalConfig)
    , mRepeatDelayEntry("Key Repeat Delay", 100, NumberEntryWidget(0, 9999, timer))
    , mRepeatRateEntry("Key Repeat Rate", 100, NumberEntryWidget(0, 9999, timer))
    , mSaveButton("Save")
    , mItems({{ mRepeatDelayEntry,
                mRepeatRateEntry,
                mSaveButton }})
    , mHStackWidget(mItems, true)
    , mNext(next)
{
    mRepeatDelayEntry.widget.value = mGlobalConfig.keyRepeatDelay;
    mRepeatRateEntry.widget.value  = mGlobalConfig.keyRepeatRate;

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
    mGlobalConfig.keyRepeatDelay = mRepeatDelayEntry.widget.value;
    mGlobalConfig.keyRepeatRate  = mRepeatRateEntry.widget.value;

    mNext.processEvent(ScreenEvent::create(ScreenEvent::Type::kHome));
}

