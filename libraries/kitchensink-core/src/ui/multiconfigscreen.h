#ifndef INCLUDED_MULTICONFIGSCREEN_H
#define INCLUDED_MULTICONFIGSCREEN_H

#include "event/eventstage.h"
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
    virtual void screenExit() override;

private:
    typedef std::array<LabelledWidget<EventEntryWidget>,
                       Config::kMultiKeyTapCount> EventEntryWidgets;

private:
    MultiKey&                                          mMultiKey;
    LabelledWidget<TextEntryWidget>                    mTitleEntry;
    EventEntryWidgets                                  mEventEntry;
    HStackWidget::Items<1 + Config::kMultiKeyTapCount> mItems;
    HStackWidget                                       mHStackWidget;
    EventStage&                                        mNext;
};

#endif
