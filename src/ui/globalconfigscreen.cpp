#include "ui/globalconfigscreen.h"

GlobalConfigScreen::GlobalConfigScreen(Timer&        timer,
                                       GlobalConfig& globalConfig,
                                       EventStage&   next)
    : mGlobalConfig(globalConfig)
    , mRepeatDelayEntry("Key Repeat Delay", 100, TextEntryWidget(timer))
    , mRepeatRateEntry("Key Repeat Rate", 100, TextEntryWidget(timer))
    , mItems({{ mRepeatDelayEntry,
                mRepeatRateEntry }})
    , mHStackWidget(mItems, true)
    , mNext(next)
{ }

bool GlobalConfigScreen::processEvent(const Event& event)
{
    return mHStackWidget.processEvent(event);
}

Widget& GlobalConfigScreen::rootWidget()
{
    return mHStackWidget;
}

