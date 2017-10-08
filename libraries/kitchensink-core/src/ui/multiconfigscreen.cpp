#include "ui/multiconfigscreen.h"

#include "multikey.h"
#include "types/arrayutil.h"
#include "types/stroutstream.h"

MultiConfigScreen::MultiConfigScreen(TimerManager&      timer,
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
}

bool MultiConfigScreen::processEvent(const Event& event)
{
    return mHStackWidget.processEvent(event);
}

Widget& MultiConfigScreen::rootWidget()
{
    return mHStackWidget;
}

void MultiConfigScreen::screenExit()
{
    mMultiKey.name = mTitleEntry.widget.text;

    for (std::size_t i(0); i < mEventEntry.size(); ++i)
    {
        mMultiKey.events[i] = mEventEntry[i].widget.event;
    }
}
