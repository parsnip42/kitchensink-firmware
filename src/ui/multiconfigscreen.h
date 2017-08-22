#ifndef INCLUDED_MULTICONFIGSCREEN_H
#define INCLUDED_MULTICONFIGSCREEN_H

#include "ui/screen.h"
#include "ui/labelledwidget.h"
#include "ui/textentrywidget.h"
#include "ui/evententrywidget.h"
#include "ui/hstackwidget.h"

class Timer;
class MultiKey;

class MultiConfigScreen : public Screen
{
public:
    MultiConfigScreen(Timer&    timer,
                      MultiKey& multiKey);

public:
    virtual void processEvent(const Event& event) override;
    virtual Widget& rootWidget() override;

private:
    MultiKey&                                       mMultiKey;
    LabelledWidget<TextEntryWidget>                 mTitleEntry;
    std::array<LabelledWidget<EventEntryWidget>, 2> mEventEntry;
    HStackWidget::Items<3>                          mItems;
    HStackWidget                                    mHStackWidget;
};

#endif
