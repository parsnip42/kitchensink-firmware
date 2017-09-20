#include "ui/globalconfigscreen.h"

#include "globalconfig.h"
#include "event/screenevent.h"
#include "types/stroutstream.h"

#include "types/arrayutil.h"


GlobalConfigScreen::GlobalConfigScreen(Timer&        timer,
                                       GlobalConfig& globalConfig,
                                       EventStage&   next)
    : mGlobalConfig(globalConfig)
    , mTapDelayEntry("Multi Tap Delay", 140, NumberEntryWidget(0, 9999, timer))
    , mRepeatDelayEntry("Key Repeat Delay", 140, NumberEntryWidget(0, 9999, timer))
    , mRepeatRateEntry("Key Repeat Rate", 140, NumberEntryWidget(0, 9999, timer))
    , mHomeScreenColumns("Home Screen Columns", 140, NumberEntryWidget(1, 9, timer))
    , mHomeScreenTimeout("Home Screen Timeout", 140, NumberEntryWidget(0, 999999, timer))
    , mHomeScreenLeds(ArrayUtil<HomeLedWidgets>::createArray([&](int i)
                      {
                          StrBuf<24> name;
                          StrOutStream out(name);

                          out.appendStr("Home Widget ");
                          out.appendInt(i + 1);
                          
                          return LabelledWidget<NumberEntryWidget>(name, 140, NumberEntryWidget(0, 999999, timer));
                      }))
    , mSaveButton("Save")
    , mItems({{ mTapDelayEntry,
                mRepeatDelayEntry,
                mRepeatRateEntry,
                mHomeScreenColumns,
                mHomeScreenTimeout }})
    , mHStackWidget(mItems, true)
    , mNext(next)
{
    for (std::size_t i(0); i < Config::kHomeLedCount; ++i)
    {
        mItems[5 + i] = HStackWidget::Element(mHomeScreenLeds[i]);
    }
    mItems[5 + Config::kHomeLedCount] = HStackWidget::Element(mSaveButton);
    
    mTapDelayEntry.widget.value      = mGlobalConfig.tapDelay;
    mRepeatDelayEntry.widget.value   = mGlobalConfig.keyRepeatDelay;
    mRepeatRateEntry.widget.value    = mGlobalConfig.keyRepeatRate;
    mHomeScreenColumns.widget.value  = mGlobalConfig.homeScreenColumns;
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
    mGlobalConfig.homeScreenColumns = mHomeScreenColumns.widget.value;
    mGlobalConfig.homeScreenTimeout = mHomeScreenTimeout.widget.value;
    
    mNext.processEvent(ScreenEvent::create(ScreenEvent::Type::kHome));
}

