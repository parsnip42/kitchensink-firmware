#include "ui/homescreen.h"

HomeScreen::HomeScreen(Timer&         timer,
                       KeyEventStage& next)
    : mDisplayTimeout(timer.createHandle())
    , mNext(next)
{
    mHomeWidget.entries[0].text = "Num Lock";
    mHomeWidget.entries[0].visible = true;
    
    mHomeWidget.entries[1].text = "Caps Lock";
    mHomeWidget.entries[1].visible = true;
    
    mHomeWidget.entries[2].text = "Scroll Lock";
    mHomeWidget.entries[2].visible = true;

    mDisplayTimeout.schedule(10000);
}

void HomeScreen::processKeyEvent(const KeyEvent& event)
{
    if (mDisplayTimeout.matches(event))
    {
        mHomeWidget.visible = false;
        mHomeWidget.invalidateWidget();
        return;
    }

    auto keyId(event.keyId);

    if (keyId.type() == KeyId::Type::kLedMask)
    {
        auto mask(keyId.value());
        
        mHomeWidget.entries[0].value = mask & KeyId::NumLock;
        mHomeWidget.entries[1].value = mask & KeyId::CapsLock;
        mHomeWidget.entries[2].value = mask & KeyId::ScrollLock;

        update();
        return;
    }
    
    mNext.processKeyEvent(event);
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


