#include "ui/editmacroscreen.h"

#include "ui/labelwidget.h"
#include "ui/surface.h"
#include "ui/combowidget.h"
#include "ui/focusutil.h"
#include "ui/keys.h"
#include "ui/recordmacroscreen.h"
#include "autorepeat.h"
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

EditMacroScreen::EditMacroScreen(Timer&    timer,
                                 MacroSet& macroSet,
                                 Macro&    macro)
    : mMacroSet(macroSet)
    , mMacro(macro)
    , mTitleEntry("Name", Justify::kLeft,
                  TextEntryWidget(timer),
                  kLabelWidth)
    , mShortcutEntry("Shortcut", Justify::kLeft,
                     TextEntryWidget(timer),
                     kLabelWidth)
    , mTypeCombo("Type", Justify::kLeft,
                 ComboWidget(mtds),
                 kLabelWidth)
    , mWidgetSet({ &mTitleEntry, &mShortcutEntry, &mTypeCombo })
    , mListWidget(mWidgetSet.begin(), mWidgetSet.end(), TextEntryWidget::kPreferredHeight)
    , mHSplit(mTitleWidget,
              mListWidget,
              TitleWidget::kPreferredHeight + 1)
{
    StrOStream os(mTitleWidget.text);

    os.appendStr("Configuring Macro");
    
    mTitleEntry.widget.text = mMacro.name;
    mShortcutEntry.widget.text = mMacro.shortcut;    
    mTypeCombo.widget.selectedItem = 0;
}

void EditMacroScreen::processKeyEvent(const KeyEvent& event)
{
    auto keyId(event.keyId);

    if (Keys::ok(keyId) && mListWidget.lastWidgetFocused())
    {
        if (event.pressed)
        {
            // MacroType macroType((mTypeCombo.widget.selectedItem == 2) ?
            //                     MacroType::kInvert :
            //                     MacroType::kSync);

            // mMacro.type     = macroType;
            // mMacro.name     = mTitleEntry.widget.text;
            // mMacro.shortcut = mShortcutEntry.widget.text;

            // RecordMacroScreen record(mSurface,
            //                          mEventManager,
            //                          mMacro,
            //                          (mTypeCombo.widget.selectedItem == 1));

            // record.poll();

            // Storage storage;
            // Serializer<MacroSet> s;
                
            // auto os(storage.write(Storage::Region::Macro));
                
            // s.serialize(mMacroSet, os);
            // mQuit = true;
        }
    }
    else
    {
        mListWidget.processKeyEvent(event);
    }
}

Widget& EditMacroScreen::rootWidget()
{
    return mHSplit;
}
