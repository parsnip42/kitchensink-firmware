#include "ui/multiconfigscreen.h"

MultiConfigScreen::MultiConfigScreen(Timer&    timer,
                                     MultiKey& multiKey)
    : mMultiKey(multiKey)
    , mTitleEntry("Name", 70, TextEntryWidget(timer))
    , mEventEntry({{
                LabelledWidget<EventEntryWidget>("Tap 1", 70, EventEntryWidget(timer)),
                LabelledWidget<EventEntryWidget>("Tap 2", 70, EventEntryWidget(timer)),
                LabelledWidget<EventEntryWidget>("Tap 3", 70, EventEntryWidget(timer)),
                LabelledWidget<EventEntryWidget>("Tap 4", 70, EventEntryWidget(timer))
                }})
    , mItems({{ mTitleEntry, mEventEntry[0], mEventEntry[1], mEventEntry[2], mEventEntry[3] }})
    , mHStackWidget(mItems, true)
{ }

bool MultiConfigScreen::processEvent(const Event& event)
{
    return mHStackWidget.processEvent(event);
}

Widget& MultiConfigScreen::rootWidget()
{
    return mHStackWidget;
}
