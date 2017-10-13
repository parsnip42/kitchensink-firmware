#ifndef INCLUDED_STATUSSCREEN_H
#define INCLUDED_STATUSSCREEN_H

#include "ui/hstackwidget.h"
#include "ui/propertywidget.h"
#include "ui/widgetset.h"
#include "ui/screen.h"

class KeyboardState;
class EventManager;
class TimerManager;
class Widget;

class StatusScreen : public Screen
{
public:
    explicit StatusScreen(KeyboardState& keyboardState,
                          EventManager&  eventManager,
                          TimerManager&  timerManager);

public:
    virtual bool processEvent(const Event& event) override;
    virtual void screenInit() override;
    virtual Widget& rootWidget() override;

private:
    KeyboardState&         mKeyboardState;
    EventManager&          mEventManager;
    TimerManager&          mTimerManager;
    PropertyWidget         mMemoryUsage;
    PropertyWidget         mConfigSize;
    PropertyWidget         mScanRate;
    PropertyWidget         mAllocatedTimers;
    PropertyWidget         mActiveTimers;
    PropertyWidget         mMacroPoolUsage;
    PropertyWidget         mSMacroPoolUsage;
    HStackWidget::Items<7> mItems;
    HStackWidget           mHStackWidget;
};

#endif
