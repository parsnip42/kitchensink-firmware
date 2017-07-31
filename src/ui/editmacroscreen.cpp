#include "ui/editmacroscreen.h"

#include "ui/tablelayout.h"
#include "ui/labelwidget.h"
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
                  eventManager,
                  *this)
    , mShortcutEntry(surface,
                     eventManager,
                     *this)
    , mTypeCombo(surface,
                 eventManager,
                 *this,
                 mtds)
    , mFocused(&mTitleEntry)
    , mQuit(false)
{
    mTitleEntry.text = mMacro.name;
    mShortcutEntry.text = mMacro.shortcut;
    mTypeCombo.selectedItem = 0;

    mFocused->setFocused(true);
}

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
    TableLayout layout(72, Surface::kWidth, 16, 8, 2);
                
    LabelWidget la(layout.next(),
                   "Name",
                   LabelWidget::Justify::kRight);

    mTitleEntry.region = layout.next();
                
    LabelWidget lb(layout.next(),
                   "Shortcut",
                   LabelWidget::Justify::kRight);
    
    mShortcutEntry.region = layout.next();

    MacroTypeDataSource ds;
                
    LabelWidget lc(layout.next(),
                   "Type",
                   LabelWidget::Justify::kRight);

    mTypeCombo.region = layout.next();

    for (int y(0); y < Surface::kHeight; ++y)
    {
        Surface::RowData row;

        Surface::render(la, row, y);
        Surface::render(lb, row, y);
        Surface::render(lc, row, y);

        Surface::render(mTitleEntry, row, y);
        Surface::render(mShortcutEntry, row, y);
        Surface::render(mTypeCombo, row, y);

        mSurface.render(row, y);
    }
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
