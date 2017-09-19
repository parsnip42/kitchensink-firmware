#ifndef INCLUDED_GLOBALCONFIGSCREEN_H
#define INCLUDED_GLOBALCONFIGSCREEN_H

#include "ui/labelledwidget.h"
#include "ui/combowidget.h"
#include "ui/hstackwidget.h"
#include "ui/screen.h"
#include "ui/textentrywidget.h"

class GlobalConfig;
class Timer;

class GlobalConfigScreen : public Screen
{
public:
    GlobalConfigScreen(Timer&        timer,
                       GlobalConfig& globalConfig,
                       EventStage&   next);
    
public:
    virtual bool processEvent(const Event& event) override;
    virtual Widget& rootWidget() override;

private:
    GlobalConfig&                   mGlobalConfig;
    LabelledWidget<TextEntryWidget> mRepeatDelayEntry;
    LabelledWidget<TextEntryWidget> mRepeatRateEntry;
    HStackWidget::Items<2>          mItems;
    HStackWidget                    mHStackWidget;
    EventStage&                     mNext;
};

#endif
