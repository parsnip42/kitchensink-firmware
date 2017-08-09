#include "keyconfigscreen.h"

KeyConfigScreen::KeyConfigScreen()
    : mLabel("TEST")
{ }

void KeyConfigScreen::processKeyEvent(const KeyEvent& event)
{
    
}

Widget& KeyConfigScreen::rootWidget()
{
    return mLabel;
}
