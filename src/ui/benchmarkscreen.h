#ifndef INCLUDED_BENCHMARKSCREEN_H
#define INCLUDED_BENCHMARKSCREEN_H

#include "ui/hstackwidget.h"
#include "ui/labelwidget.h"
#include "ui/widgetset.h"
#include "event/eventstage.h"

class EventManager;
class Widget;

class BenchmarkScreen : public EventStage
{
public:
    explicit BenchmarkScreen(EventManager& eventManager);

public:
    virtual void processEvent(const Event& event) override;
    void run();
    Widget& rootWidget();

private:
    EventManager&          mEventManager;
    LabelWidget            mStatusLabel;
    HStackWidget::Items<1> mItems;
    HStackWidget           mHStackWidget;
};

#endif
