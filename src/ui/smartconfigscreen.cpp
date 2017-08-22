#include "ui/smartconfigscreen.h"

#include "types/arrayobjectsource.h"

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
    , mEventEntry("Current", 70, EventEntryWidget(timer))
    , mAuxEventEntry("Current", 70, EventEntryWidget(timer))
    , mItems({{ mTitleEntry, mTypeCombo, mEventEntry, mAuxEventEntry }})
    , mHStackWidget(mItems, true)
{ }

void SmartConfigScreen::processEvent(const Event& event)
{
    mHStackWidget.processEvent(event);
}

Widget& SmartConfigScreen::rootWidget()
{
    return mHStackWidget;
}
