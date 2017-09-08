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

EditMacroScreen::EditMacroScreen(Timer&       timer,
                                 MacroSet&    macroSet,
                                 int          macroId,
                                 EventStage&  next)
    : mMacroSet(macroSet)
    , mMacroId(macroId)
    , mTitleEntry("Name",
                  kLabelWidth,
                  TextEntryWidget(timer))
    , mShortcutEntry("Shortcut",
                     kLabelWidth,
                     TextEntryWidget(timer))
    , mTypeCombo("Type",
                 kLabelWidth,
                 ComboWidget(mtds))
    , mRecordButton("Record")
    , mItems({{ mTitleEntry,
                mShortcutEntry,
                mTypeCombo,
                mRecordButton }})
    , mHStackWidget(mItems, true)
    , mNext(next)
{
    auto& macro(mMacroSet[mMacroId]);

    mTitleEntry.widget.text        = macro.name;
    mShortcutEntry.widget.text     = macro.shortcut;
    mTypeCombo.widget.selectedItem = static_cast<int>(macro.type);
    
    mRecordButton.activated = Action::memFn<EditMacroScreen,
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

void EditMacroScreen::onRecord()
{
    auto& macro(mMacroSet[mMacroId]);
                
    auto macroType(static_cast<Macro::Type>(mTypeCombo.widget.selectedItem));
                
    macro.type     = macroType;
    macro.name     = mTitleEntry.widget.text;
    macro.shortcut = mShortcutEntry.widget.text;
                
    mNext.processEvent(ScreenEvent::create(ScreenEvent::Type::kRecordMacro, mMacroId));
}





