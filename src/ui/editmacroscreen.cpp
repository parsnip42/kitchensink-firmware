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
    , mItems({{ mTitleEntry, mShortcutEntry, mTypeCombo }})
    , mHStackWidget(mItems, true)
    , mNext(next)
{
    auto& macro(mMacroSet[mMacroId]);

    mTitleEntry.widget.text        = macro.name;
    mShortcutEntry.widget.text     = macro.shortcut;
    mTypeCombo.widget.selectedItem = 0;
}

void EditMacroScreen::processEvent(const Event& event)
{
    if (Keys::ok(event) && &mHStackWidget.focused() == &mTypeCombo)
    {
        auto& macro(mMacroSet[mMacroId]);
            
        MacroType macroType((mTypeCombo.widget.selectedItem == 2) ?
                            MacroType::kInvert :
                            MacroType::kSync);

        macro.type     = macroType;
        macro.name     = mTitleEntry.widget.text;
        macro.shortcut = mShortcutEntry.widget.text;

        auto realtime(mTypeCombo.widget.selectedItem == 1);
        auto screenType(realtime ? ScreenEvent::Type::kRecordMacroRT : ScreenEvent::Type::kRecordMacro);
            
        mNext.processEvent(ScreenEvent::create(screenType, mMacroId));        
    }
    else
    {
        mHStackWidget.processEvent(event);
    }
}

Widget& EditMacroScreen::rootWidget()
{
    return mHStackWidget;
}
