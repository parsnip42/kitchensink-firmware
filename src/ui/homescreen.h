#ifndef INCLUDED_HOMESCREEN_H
#define INCLUDED_HOMESCREEN_H

#include "ui/homewidget.h"
#include "eventstage.h"
#include "timer.h"
#include "smartkeyset.h"

class Widget;

class HomeScreen : public EventStage
{
public:
    HomeScreen(Timer&             timer,
               const SmartKeySet& smartKeySet,
               EventStage&        next);

public:
    virtual void processEvent(const Event& event) override;

    Widget& rootWidget();

    void update();
    
private:
    Timer::Handle      mDisplayTimeout;
    const SmartKeySet& mSmartKeySet;
    HomeWidget         mHomeWidget;
    EventStage&        mNext;
};

#endif
