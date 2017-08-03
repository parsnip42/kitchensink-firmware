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

}

EditMacroScreen::EditMacroScreen(Surface&      surface,
                                 EventManager& eventManager,
                                 MacroSet&     macroSet,
                                 Macro&        macro)
    : mSurface(surface)
    , mEventManager(eventManager)
    , mMacroSet(macroSet)
    , mMacro(macro)
    , mTitleEntry("Name", Justify::kRight,
                  TextEntryWidget(eventManager),
                  30, 4)
    , mShortcutEntry("Shortcut", Justify::kRight,
                     TextEntryWidget(eventManager),
                     30, 4)
    , mTypeCombo("Type", Justify::kRight,
                 ComboWidget(mtds),
                 30, 4)
    , mListWidget(16, 2,
                    { &mTitleEntry, &mShortcutEntry, &mTypeCombo } )
    , mQuit(false)
{
    mTitleEntry.widget.text = mMacro.name;
    mShortcutEntry.widget.text = mMacro.shortcut;    
    mTypeCombo.widget.selectedItem = 0;
}

void EditMacroScreen::poll()
{
    Surface::WidgetGuard guard(mSurface, mListWidget);

    AutoRepeat autoRepeat(mEventManager.timer,
                          *this);
    while (!mQuit)
    {
        mEventManager.poll(autoRepeat);
    }
}

void EditMacroScreen::processKeyEvent(const KeyEvent& event)
{
    mListWidget.processKeyEvent(event);

    if (event.pressed)
    {
        auto keyId(event.keyId);

        if (Keys::ok(keyId))
        {
            MacroType macroType((mTypeCombo.widget.selectedItem == 2) ?
                                MacroType::kInvert :
                                MacroType::kSync);

            mMacro.type = macroType;
            mMacro.name = mTitleEntry.widget.text;
            mMacro.shortcut = mShortcutEntry.widget.text;

            RecordMacroScreen record(mSurface,
                                     mEventManager,
                                     mMacro,
                                     (mTypeCombo.widget.selectedItem == 1));

            record.poll();

            Storage storage;
            Serializer<MacroSet> s;
                
            auto os(storage.write(Storage::Region::Macro));
                
            s.serialize(mMacroSet, os);

            mSurface.clear();

            mQuit = true;
        }
        else if (Keys::cancel(keyId))
        {
            mSurface.clear();
            mQuit = true;
        }
    }
}
