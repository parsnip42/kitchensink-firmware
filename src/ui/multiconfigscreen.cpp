#include "ui/multiconfigscreen.h"

MultiConfigScreen::MultiConfigScreen(Timer&    timer,
                                     MultiKey& multiKey)
    : mMultiKey(multiKey)
    , mTitleEntry("Name", 70, TextEntryWidget(timer))
    , mEventEntry("Tap 1", 70, EventEntryWidget(timer))
    , mItems({{ mTitleEntry, mEventEntry }})
    , mHStackWidget(mItems, true)
{ }

void MultiConfigScreen::processEvent(const Event& event)
{
    mHStackWidget.processEvent(event);
}

Widget& MultiConfigScreen::rootWidget()
{
    return mHStackWidget;
}
