#include "ui/editmacroscreen.h"

#include "ui/labelwidget.h"
#include "ui/surface.h"
#include "ui/combowidget.h"
#include "ui/focusutil.h"
#include "ui/keys.h"
#include "types/arrayobjectsource.h"
#include "storage/storage.h"
#include "serialize/serializer.h"
#include "macro.h"

namespace
{

const std::array<ComboWidget::Item, 3> typeCombo = {{
        StrRef("Normal"),
        StrRef("Realtime"),
        StrRef("Key Combination")
    }};

ArrayObjectSource<ComboWidget::Item> mtds(typeCombo.begin(), typeCombo.end());

constexpr int kLabelWidth = Font::width("Shortcut ");

}

EditMacroScreen::EditMacroScreen(Timer&      timer,
                                 Macro&      macro,
                                 Event       recordEvent,
                                 EventStage& next)
    : mMacro(macro)
    , mTitleEntry("Name",
                  kLabelWidth,
                  TextEntryWidget(timer))
    , mShortcutEntry("Shortcut",
                     kLabelWidth,
                     TextEntryWidget(timer))
    , mTypeCombo("Type",
                 kLabelWidth,
                 ComboWidget(mtds))
    , mItems({{ mTitleEntry,
                mShortcutEntry,
                mTypeCombo }})
    , mHStackWidget(mItems, true)
    , mRecordEvent(recordEvent)
    , mNext(next)
{
    mTitleEntry.widget.text        = mMacro.name;
    mShortcutEntry.widget.text     = mMacro.shortcut;
    mTypeCombo.widget.selectedItem = static_cast<int>(mMacro.type);
    
    mHStackWidget.applied = Action::memFn<EditMacroScreen,
                                          &EditMacroScreen::onRecord>(this);
}

bool EditMacroScreen::processEvent(const Event& event)
{
    return mHStackWidget.processEvent(event);
}

Widget& EditMacroScreen::rootWidget()
{
    return mHStackWidget;
}

void EditMacroScreen::screenExit()
{
    apply();
}

void EditMacroScreen::apply()
{
    auto macroType(static_cast<Macro::Type>(mTypeCombo.widget.selectedItem));
                
    mMacro.type     = macroType;
    mMacro.name     = mTitleEntry.widget.text;
    mMacro.shortcut = mShortcutEntry.widget.text;   
}

void EditMacroScreen::onRecord()
{
    apply();
    mNext.processEvent(mRecordEvent);
}





