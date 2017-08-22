#ifndef INCLUDED_SMARTCONFIGSCREEN_H
#define INCLUDED_SMARTCONFIGSCREEN_H

#include "ui/screen.h"
#include "ui/textentrywidget.h"
#include "ui/labelledwidget.h"
#include "ui/combowidget.h"
#include "ui/evententrywidget.h"
#include "ui/hstackwidget.h"

class Timer;
class SmartKey;

class SmartConfigScreen : public Screen
{
public:
    SmartConfigScreen(Timer&    timer,
                      SmartKey& smartKey);

public:
    virtual void processEvent(const Event& event) override;
    virtual Widget& rootWidget() override;

private:
    SmartKey&                        mSmartKey;
    LabelledWidget<TextEntryWidget>  mTitleEntry;
    LabelledWidget<ComboWidget>      mTypeCombo;
    LabelledWidget<EventEntryWidget> mEventEntry;
    LabelledWidget<EventEntryWidget> mAuxEventEntry;
    HStackWidget::Items<4>           mItems;
    HStackWidget                     mHStackWidget;
};

#endif










