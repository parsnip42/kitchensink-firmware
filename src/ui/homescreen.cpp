#include "ui/homescreen.h"

#include "event/event.h"
#include "event/ledmaskevent.h"

HomeScreen::HomeScreen(Timer&             timer,
                       const SmartKeySet& smartKeySet,
                       EventStage&     next)
    : mDisplayTimeout(timer.createHandle())
    , mSmartKeySet(smartKeySet)
    , mNext(next)
{
    mHomeWidget.entries[0].text    = "Num Lock";
    mHomeWidget.entries[0].visible = true;

    mHomeWidget.entries[1].text    = "Shift Lock";
    mHomeWidget.entries[1].visible = true;

    mHomeWidget.entries[2].text    = "Caps Lock";
    mHomeWidget.entries[2].visible = true;
    
    mHomeWidget.entries[4].text    = "Scroll Lock";
    mHomeWidget.entries[4].visible = true;

    mDisplayTimeout.schedule(10000);
}

void HomeScreen::processEvent(const Event& event)
{
    if (mDisplayTimeout.matches(event))
    {
        mHomeWidget.visible = false;
        mHomeWidget.invalidateWidget();
        return;
    }

    if (event.is<LedMaskEvent>())
    {
        auto ledMaskEvent(event.get<LedMaskEvent>());
        
        mHomeWidget.entries[0].value = ledMaskEvent.numLock();
        mHomeWidget.entries[2].value = ledMaskEvent.capsLock();
        mHomeWidget.entries[4].value = ledMaskEvent.scrollLock();

        update();
    }
    // else if (keyId.type() == KeyId::Type::kSmart)
    // {
    //     mHomeWidget.entries[1].value = mSmartKeySet[0].enabled;
    //     update();
    // }
    else
    {
        mNext.processEvent(event);
    }
}

Widget& HomeScreen::rootWidget()
{
    return mHomeWidget;
}

void HomeScreen::update()
{
    mHomeWidget.visible = true;
    mHomeWidget.invalidateWidget();
    mDisplayTimeout.schedule(10000);
}


