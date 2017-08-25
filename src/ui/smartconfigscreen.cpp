#include "ui/smartconfigscreen.h"

#include "types/arrayobjectsource.h"
#include "smartkey.h"

namespace
{

const std::array<ComboWidget::Item, 5> typeCombo = {{
        StrRef("Toggle"),
        StrRef("Toggle + AutoRelease"),
        StrRef("Hold + AutoRelease"),
        StrRef("Pair"),
        StrRef("Hold / Tap")
    }};

ArrayObjectSource<ComboWidget::Item> stds(typeCombo.begin(), typeCombo.end());

}

SmartConfigScreen::SmartConfigScreen(Timer&    timer,
                                     SmartKey& smartKey)
    : mSmartKey(smartKey)
    , mTitleEntry("Name", 70, TextEntryWidget(timer))
    , mTypeCombo("Type", 70, ComboWidget(stds))
    , mEventEntry("Key", 70, EventEntryWidget(timer))
    , mAuxEventEntry("Aux Key", 70, EventEntryWidget(timer))
    , mItems({{ mTitleEntry, mTypeCombo, mEventEntry, mAuxEventEntry }})
    , mHStackWidget(mItems, true)
{
    mTitleEntry.widget.text        = mSmartKey.name;
    mTypeCombo.widget.selectedItem = static_cast<int>(mSmartKey.type);
    mEventEntry.widget.event       = mSmartKey.event;
    mAuxEventEntry.widget.event    = mSmartKey.auxEvent;
}

bool SmartConfigScreen::processEvent(const Event& event)
{
    return mHStackWidget.processEvent(event);
}

Widget& SmartConfigScreen::rootWidget()
{
    return mHStackWidget;
}









