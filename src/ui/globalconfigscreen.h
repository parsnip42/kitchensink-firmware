#ifndef INCLUDED_GLOBALCONFIGSCREEN_H
#define INCLUDED_GLOBALCONFIGSCREEN_H

#include "ui/buttonwidget.h"
#include "ui/combowidget.h"
#include "ui/homeledwidget.h"
#include "ui/hstackwidget.h"
#include "ui/labelledwidget.h"
#include "ui/numberentrywidget.h"
#include "ui/screen.h"

class GlobalConfig;
class Timer;

class GlobalConfigScreen : public Screen
{
public:
    GlobalConfigScreen(const SmartKeySet& smartKeySet,
                       GlobalConfig&      globalConfig,
                       Timer&             timer,
                       EventStage&        next);
    
public:
    virtual bool processEvent(const Event& event) override;
    virtual Widget& rootWidget() override;

private:
    void onSave();

private:
    typedef std::array<LabelledWidget<HomeLedWidget>,
                       Config::kHomeLedCount> HomeLedWidgets;
    
private:
    GlobalConfig&                                  mGlobalConfig;
    LabelledWidget<NumberEntryWidget>              mTapDelayEntry;
    LabelledWidget<NumberEntryWidget>              mRepeatDelayEntry;
    LabelledWidget<NumberEntryWidget>              mRepeatRateEntry;
    LabelledWidget<NumberEntryWidget>              mHomeScreenColumns;
    LabelledWidget<NumberEntryWidget>              mHomeScreenTimeout;
    HomeLedWidgets                                 mHomeScreenLeds;
    ButtonWidget                                   mSaveButton;
    HStackWidget::Items<6 + Config::kHomeLedCount> mItems;
    HStackWidget                                   mHStackWidget;
    EventStage&                                    mNext;
};

#endif
