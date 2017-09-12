#ifndef INCLUDED_STATUSSCREEN_H
#define INCLUDED_STATUSSCREEN_H

#include "ui/hstackwidget.h"
#include "ui/propertywidget.h"
#include "ui/widgetset.h"
#include "ui/screen.h"

class EventManager;
class Widget;

class StatusScreen : public Screen
{
public:
    explicit StatusScreen(EventManager& eventManager);

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
