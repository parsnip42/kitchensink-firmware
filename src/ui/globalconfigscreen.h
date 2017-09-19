#ifndef INCLUDED_GLOBALCONFIGSCREEN_H
#define INCLUDED_GLOBALCONFIGSCREEN_H

#include "ui/labelledwidget.h"
#include "ui/buttonwidget.h"
#include "ui/combowidget.h"
#include "ui/hstackwidget.h"
#include "ui/screen.h"
#include "ui/numberentrywidget.h"

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
    void onSave();

private:
    GlobalConfig&                     mGlobalConfig;
    LabelledWidget<NumberEntryWidget> mRepeatDelayEntry;
    LabelledWidget<NumberEntryWidget> mRepeatRateEntry;
    ButtonWidget                      mSaveButton;
    HStackWidget::Items<3>            mItems;
    HStackWidget                      mHStackWidget;
    EventStage&                       mNext;
};

#endif
