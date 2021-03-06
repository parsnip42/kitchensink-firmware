#ifndef INCLUDED_HOMESCREEN_H
#define INCLUDED_HOMESCREEN_H

#include "ui/screen.h"
#include "ui/homewidget.h"
#include "event/eventstage.h"
#include "event/ledmaskevent.h"
#include "timer/timermanager.h"
#include "smartkeyset.h"

class GlobalConfig;
class Widget;

class HomeScreen : public Screen
{
public:
    HomeScreen(const GlobalConfig& globalConfig,
               const SmartKeySet&  smartKeySet,
               TimerManager&              timer,
               EventStage&         next);

public:
    virtual bool processEvent(const Event& event) override;
    virtual Widget& rootWidget() override;


private:
    void updateKeyboardKeys(const LedMaskEvent& event);
    void updateSmartKeys();
    void show();

private:
    const GlobalConfig& mGlobalConfig;
    const SmartKeySet&  mSmartKeySet;
    Timer       mDisplayTimeout;
    HomeWidget          mHomeWidget;
    EventStage&         mNext;
};

#endif
