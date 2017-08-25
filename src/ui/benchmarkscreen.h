#ifndef INCLUDED_BENCHMARKSCREEN_H
#define INCLUDED_BENCHMARKSCREEN_H

#include "ui/hstackwidget.h"
#include "ui/propertywidget.h"
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
    virtual bool processEvent(const Event& event) override;
    virtual void screenInit() override;
    virtual Widget& rootWidget() override;

private:
    EventManager&          mEventManager;
    PropertyWidget         mMemoryUsage;
    PropertyWidget         mConfigSize;
    PropertyWidget         mScanRate;
    HStackWidget::Items<3> mItems;
    HStackWidget           mHStackWidget;
};

#endif
