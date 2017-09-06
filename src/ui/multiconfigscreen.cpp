#include "ui/multiconfigscreen.h"

#include "event/screenevent.h"
#include "multikey.h"

MultiConfigScreen::MultiConfigScreen(Timer&      timer,
                                     MultiKey&   multiKey,
                                     EventStage& next)
    : mMultiKey(multiKey)
    , mTitleEntry("Name", 70, TextEntryWidget(timer))
    , mEventEntry({{
                LabelledWidget<EventEntryWidget>("Tap 1", 70, EventEntryWidget(timer)),
                LabelledWidget<EventEntryWidget>("Tap 2", 70, EventEntryWidget(timer)),
                LabelledWidget<EventEntryWidget>("Tap 3", 70, EventEntryWidget(timer)),
                LabelledWidget<EventEntryWidget>("Tap 4", 70, EventEntryWidget(timer))
                }})
    , mSaveButton("Save")
    , mItems({{ mTitleEntry,
                mEventEntry[0],
                mEventEntry[1],
                mEventEntry[2],
                mEventEntry[3],
                mSaveButton }})
    , mHStackWidget(mItems, true)
    , mNext(next)
{
    mTitleEntry.widget.text = mMultiKey.name;

    for (std::size_t i(0); i < mEventEntry.size(); ++i)
    {
        mEventEntry[i].widget.event = multiKey.events[i];
    }

    mSaveButton.activated = Action::memFn<MultiConfigScreen,
                                          &MultiConfigScreen::onSave>(this);
}

bool MultiConfigScreen::processEvent(const Event& event)
{
    return mHStackWidget.processEvent(event);
}

Widget& MultiConfigScreen::rootWidget()
{
    return mHStackWidget;
}

void MultiConfigScreen::onSave()
{
    mMultiKey.name = mTitleEntry.widget.text;

    for (std::size_t i(0); i < mEventEntry.size(); ++i)
    {
        mMultiKey.events[i] = mEventEntry[i].widget.event;
    }

    mNext.processEvent(ScreenEvent::create(ScreenEvent::Type::kHome));
}
