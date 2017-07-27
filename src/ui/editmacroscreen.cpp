#include "ui/editmacroscreen.h"

#include "ui/tablelayout.h"
#include "ui/label.h"
#include "ui/surface.h"
#include "ui/combowidget.h"
#include "ui/focusutil.h"
#include "ui/keys.h"
#include "ui/recordmacroscreen.h"
#include "autorepeat.h"

#include "storage/storage.h"
#include "serialize/serializer.h"
#include "macro.h"

namespace
{

class MacroTypeDataSource : public ComboWidget::DataSource
{
public:
    virtual void item(ItemText&   text,
                      std::size_t index) const
    {
        switch (index)
        {
        case 0:
            text = "Normal";
            break;
            
        case 1:
            text = "Realtime";
            break;
            
        case 2:
            text = "Key Combination";
            break;
        }
    }
    
    virtual std::size_t size() const
    {
        return 3;
    }
};

MacroTypeDataSource mtds;

}

EditMacroScreen::EditMacroScreen(Surface&      surface,
                                 EventManager& eventManager,
                                 MacroSet&     macroSet,
                                 Macro&        macro)
    : mSurface(surface)
    , mEventManager(eventManager)
    , mMacroSet(macroSet)
    , mMacro(macro)
    , mTitleEntry(surface,
                  eventManager)
    , mShortcutEntry(surface,
                     eventManager)
    , mTypeCombo(surface,
                 eventManager,
                 mtds)
    , mFocused(&mTitleEntry)
    , mQuit(false)
{ }

void EditMacroScreen::poll()
{
    redraw();
    
    AutoRepeat autoRepeat(mEventManager.timer,
                          *this);
    while (!mQuit)
    {
        mEventManager.poll(autoRepeat);
    }
}

void EditMacroScreen::redraw()
{
    TableLayout layout(72, Surface::kWidth, 20, 8);
                
    Label(mSurface,
          layout.next(),
          "Name",
          Label::Justify::Right);

    mTitleEntry.region = layout.next();
    mTitleEntry.text = mMacro.name;
    mTitleEntry.redrawContent(true);
                
    Label(mSurface,
          layout.next(),
          "Shortcut",
          Label::Justify::Right);
    
    mShortcutEntry.region = layout.next();
    mShortcutEntry.text = mMacro.shortcut;
    mShortcutEntry.redrawContent(false);

    MacroTypeDataSource ds;
                
    Label(mSurface,
          layout.next(),
          "Type",
          Label::Justify::Right);

    mTypeCombo.region = layout.next();
    mTypeCombo.selectedItem = 0;
    mTypeCombo.redrawContent(false);
}

void EditMacroScreen::processKeyEvent(const KeyEvent& event)
{
    mFocused->processKeyEvent(event);

    if (event.pressed)
    {
        auto keyId(event.keyId);

        if (Keys::down(keyId))
        {
            FocusUtil::next(mFocused,
                            { &mTitleEntry, &mShortcutEntry, &mTypeCombo });
        }
        else if (Keys::up(keyId))
        {
            FocusUtil::prev(mFocused,
                            { &mTitleEntry, &mShortcutEntry, &mTypeCombo });
        }
        else if (Keys::cancel(keyId))
        {
            mSurface.clear();
            mQuit = true;
        }
        else if (Keys::ok(keyId))
        {
            if (!FocusUtil::next(mFocused,
                                 { &mTitleEntry, &mShortcutEntry, &mTypeCombo }))
            {
                MacroType macroType((mTypeCombo.selectedItem == 2) ?
                                    MacroType::kInvert :
                                    MacroType::kSync);

                mMacro.type = macroType;
                mMacro.name = mTitleEntry.text;
                mMacro.shortcut = mShortcutEntry.text;

                RecordMacroScreen record(mSurface,
                                         mEventManager,
                                         mMacro,
                                         (mTypeCombo.selectedItem == 1));

                record.poll();

                Storage storage;
                Serializer<MacroSet> s;
                
                auto os(storage.write(Storage::Region::Macro));
                
                s.serialize(mMacroSet, os);

                mSurface.clear();

                mQuit = true;
            }
        }
    }
}
