#ifndef INCLUDED_SMARTCONFIGSCREEN_H
#define INCLUDED_SMARTCONFIGSCREEN_H

#include "event/eventstage.h"
#include "ui/combowidget.h"
#include "ui/evententrywidget.h"
#include "ui/hstackwidget.h"
#include "ui/labelledwidget.h"
#include "ui/screen.h"
#include "ui/textentrywidget.h"

class Timer;
class SmartKey;

class SmartConfigScreen : public Screen
{
public:
    SmartConfigScreen(TimerManager&      timer,
                      SmartKey&   smartKey,
                      EventStage& next);

public:
    virtual bool processEvent(const Event& event) override;
    virtual Widget& rootWidget() override;
    virtual void screenExit() override;

private:
    SmartKey&                        mSmartKey;
    LabelledWidget<TextEntryWidget>  mTitleEntry;
    LabelledWidget<ComboWidget>      mTypeCombo;
    LabelledWidget<EventEntryWidget> mEventEntry;
    LabelledWidget<EventEntryWidget> mAuxEventEntry;
    HStackWidget::Items<4>           mItems;
    HStackWidget                     mHStackWidget;
    EventStage&                      mNext;
};

#endif










