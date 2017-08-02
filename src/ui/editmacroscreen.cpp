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
                  TextEntryWidget(eventManager),
                  30, 4)
    , mShortcutEntry("Shortcut", Justify::kRight,
                     TextEntryWidget(eventManager),
                     30, 4)
    , mTypeCombo("Type", Justify::kRight,
                 ComboWidget(mtds),
                 30, 4)
    , mWidgetLayout(16, 2,
                    { &mTitleEntry, &mShortcutEntry, &mTypeCombo } )
    , mQuit(false)
{
    mTitleEntry.widget.text = mMacro.name;
    mShortcutEntry.widget.text = mMacro.shortcut;    
    mTypeCombo.widget.selectedItem = 0;

    mWidgetLayout.setParent(this,
                            Rectangle(0,
                                      0,
                                      Surface::kWidth,
                                      Surface::kHeight));
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
    invalidateRegion(Rectangle(0,
                               0,
                               Surface::kWidth,
                               Surface::kHeight));
}

void EditMacroScreen::invalidateRegion(const Rectangle& region)
{
    for (auto y(region.y); y < (region.y + region.height); ++y)
    {
        Surface::RowBuf row;
        RasterLine rasterLine(row);
    
        mWidgetLayout.render(rasterLine, y);
        mSurface.render(row, y);
    }
}

void EditMacroScreen::processKeyEvent(const KeyEvent& event)
{
    mWidgetLayout.processKeyEvent(event);

    if (event.pressed)
    {
        auto keyId(event.keyId);

        if (Keys::ok(keyId))
        {
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
        }
        else if (Keys::cancel(keyId))
        {
            mSurface.clear();
            mQuit = true;
        }
    }
}
