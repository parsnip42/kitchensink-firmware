#include "ui/editmacroscreen.h"

#include "ui/labelwidget.h"
#include "ui/surface.h"
#include "ui/combowidget.h"
#include "ui/focusutil.h"
#include "ui/keys.h"
#include "screenstack.h"
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

EditMacroScreen::EditMacroScreen(ScreenStack& screenStack,
                                 Timer&       timer,
                                 MacroSet&    macroSet,
                                 int          macroId)
    : mScreenStack(screenStack)
    , mMacroSet(macroSet)
    , mMacroId(macroId)
    , mTitleEntry("Name", Justify::kLeft,
                  TextEntryWidget(timer),
                  kLabelWidth)
    , mShortcutEntry("Shortcut", Justify::kLeft,
                     TextEntryWidget(timer),
                     kLabelWidth)
    , mTypeCombo("Type", Justify::kLeft,
                 ComboWidget(mtds),
                 kLabelWidth)
    , mWidgetSet({ mTitleEntry, mShortcutEntry, mTypeCombo })
    , mHStackWidget(mWidgetSet, true)
{
    auto& macro(mMacroSet[mMacroId]);

    mTitleEntry.widget.text        = macro.name;
    mShortcutEntry.widget.text     = macro.shortcut;
    mTypeCombo.widget.selectedItem = 0;
}

void EditMacroScreen::processKeyEvent(const KeyEvent& event)
{
    auto keyId(event.keyId);

    if (Keys::ok(keyId) && mHStackWidget.lastWidgetFocused())
    {
        if (event.pressed)
        {
            auto& macro(mMacroSet[mMacroId]);
            
            MacroType macroType((mTypeCombo.widget.selectedItem == 2) ?
                                MacroType::kInvert :
                                MacroType::kSync);

            macro.type     = macroType;
            macro.name     = mTitleEntry.widget.text;
            macro.shortcut = mShortcutEntry.widget.text;

            mScreenStack.pop();

            auto realtime(mTypeCombo.widget.selectedItem == 1);
            auto screenType(realtime ? ScreenId::Type::kRecordMacroRT : ScreenId::Type::kRecordMacro);
            
            mScreenStack.push(ScreenId(screenType, mMacroId));
        }
    }
    else
    {
        mHStackWidget.processKeyEvent(event);
    }
}

Widget& EditMacroScreen::rootWidget()
{
    return mHStackWidget;
}






