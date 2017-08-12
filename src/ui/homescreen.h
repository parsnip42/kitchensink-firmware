#ifndef INCLUDED_HOMESCREEN_H
#define INCLUDED_HOMESCREEN_H

#include "ui/homewidget.h"
#include "keyeventstage.h"
#include "timer.h"
#include "smartkeyset.h"

class Widget;

class HomeScreen : public KeyEventStage
{
public:
    HomeScreen(Timer&             timer,
               const SmartKeySet& smartKeySet,
               KeyEventStage&     next);

public:
    virtual void processKeyEvent(const KeyEvent& event) override;

    Widget& rootWidget();

    void update();
    
private:
    Timer::Handle      mDisplayTimeout;
    const SmartKeySet& mSmartKeySet;
    HomeWidget         mHomeWidget;
    KeyEventStage&     mNext;
};

#endif
