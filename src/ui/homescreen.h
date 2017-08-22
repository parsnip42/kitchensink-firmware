#ifndef INCLUDED_HOMESCREEN_H
#define INCLUDED_HOMESCREEN_H

#include "ui/screen.h"
#include "ui/homewidget.h"
#include "event/eventstage.h"
#include "timer.h"
#include "smartkeyset.h"

class Widget;

class HomeScreen : public Screen
{
public:
    HomeScreen(Timer&             timer,
               const SmartKeySet& smartKeySet,
               EventStage&        next);

public:
    virtual void processEvent(const Event& event) override;
    virtual Widget& rootWidget() override;

    void update();
    
private:
    Timer::Handle      mDisplayTimeout;
    const SmartKeySet& mSmartKeySet;
    HomeWidget         mHomeWidget;
    EventStage&        mNext;
};

#endif
