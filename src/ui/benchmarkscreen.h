#ifndef INCLUDED_BENCHMARKSCREEN_H
#define INCLUDED_BENCHMARKSCREEN_H

#include "ui/hstackwidget.h"
#include "ui/labelwidget.h"
#include "ui/widgetset.h"
#include "ui/screen.h"
#include "event/eventstage.h"

class EventManager;
class Widget;

class BenchmarkScreen : public Screen
{
public:
    explicit BenchmarkScreen(EventManager& eventManager);

public:
    virtual void processEvent(const Event& event) override;
    virtual void screenInit() override;
    virtual Widget& rootWidget() override;

private:
    EventManager&          mEventManager;
    LabelWidget            mStatusLabel;
    HStackWidget::Items<1> mItems;
    HStackWidget           mHStackWidget;
};

#endif
