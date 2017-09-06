#ifndef INCLUDED_SMARTCONFIGSCREEN_H
#define INCLUDED_SMARTCONFIGSCREEN_H

#include "event/eventstage.h"
#include "ui/buttonwidget.h"
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
    SmartConfigScreen(Timer&      timer,
                      SmartKey&   smartKey,
                      EventStage& next);

public:
    virtual bool processEvent(const Event& event) override;
    virtual Widget& rootWidget() override;

private:
    void onSave();

private:
    SmartKey&                        mSmartKey;
    LabelledWidget<TextEntryWidget>  mTitleEntry;
    LabelledWidget<ComboWidget>      mTypeCombo;
    LabelledWidget<EventEntryWidget> mEventEntry;
    LabelledWidget<EventEntryWidget> mAuxEventEntry;
    ButtonWidget                     mSaveButton;
    HStackWidget::Items<5>           mItems;
    HStackWidget                     mHStackWidget;
    EventStage&                      mNext;
};

#endif










