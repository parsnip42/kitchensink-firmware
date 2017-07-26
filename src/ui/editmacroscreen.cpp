#include "ui/editmacroscreen.h"

#include "ui/tablelayout.h"
#include "ui/label.h"
#include "ui/surface.h"
#include "ui/combo.h"
#include "ui/focusutil.h"
#include "ui/keys.h"

#include "macro.h"

namespace
{

class MacroTypeDataSource : public Combo::DataSource
{
public:
    virtual void getItem(ItemText&   text,
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
    
    virtual std::size_t getItemCount() const
    {
        return 3;
    }
};

}

EditMacroScreen::EditMacroScreen(Surface&      surface,
                                 EventManager& eventManager,
                                 Macro&        macro)
    : mSurface(surface)
    , mEventManager(eventManager)
    , mMacro(macro)
    , mTitleEntry(surface,
                  eventManager)
    , mShortcutEntry(surface,
                     eventManager)
    , mFocused(&mTitleEntry)
{ }

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

    // Combo combo(mSurface,
    //             mKeyProcessor,
    //             layout.next(),
    //             ds,
    //             0);

}

bool EditMacroScreen::processKeyEvent(const KeyEvent& event,
                                      KeyEventStage&  next)
{
    mFocused->processKeyEvent(event);

    if (event.pressed)
    {
        auto keyId(event.keyId);

        if (Keys::ok(keyId) || Keys::down(keyId))
        {
            if (!FocusUtil::next(mFocused,
                                 { &mTitleEntry, &mShortcutEntry }))
            {
                mSurface.clear();
                return false;
            }
        }
        else if (Keys::up(keyId))
        {
            FocusUtil::prev(mFocused,
                            { &mTitleEntry, &mShortcutEntry });
        }

    }
        
    return true;
}
