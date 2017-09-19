#ifndef INCLUDED_HOMESCREEN_H
#define INCLUDED_HOMESCREEN_H

#include "ui/screen.h"
#include "ui/homewidget.h"
#include "event/eventstage.h"
#include "timer.h"
#include "smartkeyset.h"

class GlobalConfig;
class Widget;

class HomeScreen : public Screen
{
public:
    HomeScreen(const GlobalConfig& globalConfig,
               const SmartKeySet&  smartKeySet,
               Timer&              timer,
               EventStage&         next);

public:
    virtual bool processEvent(const Event& event) override;
    virtual Widget& rootWidget() override;

    void update();
    
private:
    const GlobalConfig& mGlobalConfig;
    const SmartKeySet&  mSmartKeySet;
    Timer::Handle       mDisplayTimeout;
    HomeWidget          mHomeWidget;
    EventStage&         mNext;
};

#endif
