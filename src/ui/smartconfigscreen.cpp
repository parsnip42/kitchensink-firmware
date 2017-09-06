#include "ui/smartconfigscreen.h"

#include "event/screenevent.h"
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

SmartConfigScreen::SmartConfigScreen(Timer&      timer,
                                     SmartKey&   smartKey,
                                     EventStage& next)
    : mSmartKey(smartKey)
    , mTitleEntry("Name", 70, TextEntryWidget(timer))
    , mTypeCombo("Type", 70, ComboWidget(stds))
    , mEventEntry("Key", 70, EventEntryWidget(timer))
    , mAuxEventEntry("Aux Key", 70, EventEntryWidget(timer))
    , mSaveButton("Save")
    , mItems({{ mTitleEntry,
                mTypeCombo,
                mEventEntry,
                mAuxEventEntry,
                mSaveButton }})
    , mHStackWidget(mItems, true)
    , mNext(next)
{
    mTitleEntry.widget.text        = mSmartKey.name;
    mTypeCombo.widget.selectedItem = static_cast<int>(mSmartKey.type);
    mEventEntry.widget.event       = mSmartKey.event;
    mAuxEventEntry.widget.event    = mSmartKey.auxEvent;

    mSaveButton.activated = Action::memFn<SmartConfigScreen,
                                          &SmartConfigScreen::onSave>(this);
}

bool SmartConfigScreen::processEvent(const Event& event)
{
    return mHStackWidget.processEvent(event);
}

Widget& SmartConfigScreen::rootWidget()
{
    return mHStackWidget;
}

void SmartConfigScreen::onSave()
{
    mSmartKey.name     = mTitleEntry.widget.text;
    mSmartKey.type     = static_cast<SmartKey::Type>(mTypeCombo.widget.selectedItem);
    mSmartKey.event    = mEventEntry.widget.event;
    mSmartKey.auxEvent = mAuxEventEntry.widget.event;

    mNext.processEvent(ScreenEvent::create(ScreenEvent::Type::kHome));
}
