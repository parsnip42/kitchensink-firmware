#include "keyconfigscreen.h"

KeyConfigScreen::KeyConfigScreen()
    : mLayerLabel("Layer", 50)
    , mRowLabel("Row", 50)
    , mColumnLabel("Column", 50)
    , mItems({{ mLayerLabel, mRowLabel, mColumnLabel }})
    , mHStackWidget(mItems, true)
{
    mHStackWidget.setFocused(false);
}

void KeyConfigScreen::processEvent(const Event& event)
{
    mLayerLabel.widget.text  = "1";
    mRowLabel.widget.text    = "3";
    mColumnLabel.widget.text = "7";
}

Widget& KeyConfigScreen::rootWidget()
{
    return mHStackWidget;
}
