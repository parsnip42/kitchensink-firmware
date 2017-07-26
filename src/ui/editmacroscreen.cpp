#include "ui/editmacroscreen.h"

#include "ui/tablelayout.h"
#include "ui/textentry.h"
#include "ui/label.h"
#include "ui/surface.h"
#include "ui/combo.h"

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
{ }

void EditMacroScreen::redraw()
{
    TableLayout layout(72, Surface::kWidth, 20, 8);
                
    Label(mSurface,
          layout.next(),
          "Name",
          Label::Justify::Right);

    // TextEntry titleEntry(mSurface,
    //                      mKeyProcessor,
    //                      layout.next(),
    //                      mMacro.name);
                
    Label(mSurface,
          layout.next(),
          "Shortcut",
          Label::Justify::Right);
                
    // TextEntry shortcutEntry(mSurface,
    //                         mKeyProcessor,
    //                         layout.next(),
    //                         mMacro.shortcut);

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
    return true;
}
