#include "ui/multiconfigscreen.h"

MultiConfigScreen::MultiConfigScreen(Timer&    timer,
                                     MultiKey& multiKey)
    : mMultiKey(multiKey)
    , mTitleEntry("Name", 70, TextEntryWidget(timer))
    , mEventEntry({{
                LabelledWidget<EventEntryWidget>("Tap 1", 70, EventEntryWidget(timer)),
                LabelledWidget<EventEntryWidget>("Tap 2", 70, EventEntryWidget(timer))
                }})
    , mItems({{ mTitleEntry, mEventEntry[0], mEventEntry[1] }})
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
