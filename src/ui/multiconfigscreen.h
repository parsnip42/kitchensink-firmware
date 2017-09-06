#ifndef INCLUDED_MULTICONFIGSCREEN_H
#define INCLUDED_MULTICONFIGSCREEN_H

#include "event/eventstage.h"
#include "ui/buttonwidget.h"
#include "ui/evententrywidget.h"
#include "ui/hstackwidget.h"
#include "ui/labelledwidget.h"
#include "ui/screen.h"
#include "ui/textentrywidget.h"

class Timer;
class MultiKey;

class MultiConfigScreen : public Screen
{
public:
    MultiConfigScreen(Timer&      timer,
                      MultiKey&   multiKey,
                      EventStage& next);

public:
    virtual bool processEvent(const Event& event) override;
    virtual Widget& rootWidget() override;

private:
    void onSave();
    
private:
    MultiKey&                                       mMultiKey;
    LabelledWidget<TextEntryWidget>                 mTitleEntry;
    std::array<LabelledWidget<EventEntryWidget>, 4> mEventEntry;
    ButtonWidget                                    mSaveButton;
    HStackWidget::Items<6>                          mItems;
    HStackWidget                                    mHStackWidget;
    EventStage&                                     mNext;
};

#endif
