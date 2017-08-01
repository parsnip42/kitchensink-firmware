#include "ui/editmacroscreen.h"

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
    , mTitleEntry("Name", Justify::kRight,
                  TextEntryWidget(surface,
                                  eventManager,
                                  *this),
                  30, 4)
    , mShortcutEntry("Shortcut", Justify::kRight,
                     TextEntryWidget(surface,
                                     eventManager,
                                     *this),
                     30, 4)
    , mTypeCombo("Type", Justify::kRight,
                 ComboWidget(surface,
                             eventManager,
                             *this,
                             mtds),
                 30, 4)
    , mWidgetLayout(Surface::kWidth, Surface::kHeight, 16, 2,
                    { &mTitleEntry, &mShortcutEntry, &mTypeCombo } )
    , mQuit(false)
{
    mTitleEntry.widget.text = mMacro.name;
    mShortcutEntry.widget.text = mMacro.shortcut;    
    mTypeCombo.widget.selectedItem = 0;
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
    for (int y(0); y < Surface::kHeight; ++y)
    {
        Surface::RowBuf row;

        Surface::RowData rowData(row);
        
        mWidgetLayout.render(rowData, y);
        mSurface.render(row, y);
    }
}
void EditMacroScreen::invalidateWidget(Widget&          widget,
                                       const Rectangle& region)
{
    redraw();
}

void EditMacroScreen::processKeyEvent(const KeyEvent& event)
{
    mWidgetLayout.processKeyEvent(event);

    if (event.pressed)
    {
        auto keyId(event.keyId);

        if (Keys::ok(keyId))
        {
            // if (!FocusUtil::next(mFocused,
            //                      { &mTitleEntry, &mShortcutEntry, &mTypeCombo }))
            // {
            //     MacroType macroType((mTypeCombo.widget.selectedItem == 2) ?
            //                         MacroType::kInvert :
            //                         MacroType::kSync);

            //     mMacro.type = macroType;
            //     mMacro.name = mTitleEntry.widget.text;
            //     mMacro.shortcut = mShortcutEntry.widget.text;

            //     RecordMacroScreen record(mSurface,
            //                              mEventManager,
            //                              mMacro,
            //                              (mTypeCombo.widget.selectedItem == 1));

            //     record.poll();

            //     Storage storage;
            //     Serializer<MacroSet> s;
                
            //     auto os(storage.write(Storage::Region::Macro));
                
            //     s.serialize(mMacroSet, os);

            //     mSurface.clear();

            //     mQuit = true;
            // }
        }
        else if (Keys::cancel(keyId))
        {
            mSurface.clear();
            mQuit = true;
        }
    }
}
