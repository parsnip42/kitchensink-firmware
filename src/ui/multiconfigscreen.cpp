#include "ui/multiconfigscreen.h"

#include "event/screenevent.h"
#include "multikey.h"
#include "types/arrayutil.h"
#include "types/stroutstream.h"

MultiConfigScreen::MultiConfigScreen(Timer&      timer,
                                     MultiKey&   multiKey,
                                     EventStage& next)
    : mMultiKey(multiKey)
    , mTitleEntry("Name", 70, TextEntryWidget(timer))
    , mEventEntry(ArrayUtil<EventEntryWidgets>::createArray([&](std::size_t index)
                  {
                      StrBuf<24> name;
                      StrOutStream out(name);
                      
                      out.appendStr("Tap ");
                      out.appendInt(index + 1);
                      
                      return LabelledWidget<EventEntryWidget>(name, 140, EventEntryWidget(timer));
                  }))
    , mSaveButton("Save")
    , mItems({{ mTitleEntry }})
    , mHStackWidget(mItems, true)
    , mNext(next)
{
    mTitleEntry.widget.text = mMultiKey.name;
    
    for (std::size_t i(0); i < mEventEntry.size(); ++i)
    {
        auto& entry(mEventEntry[i]);
        
        entry.widget.event = multiKey.events[i];
        mItems[i + 1] = entry;
    }

    mItems[mEventEntry.size() + 1] = mSaveButton;
    
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
