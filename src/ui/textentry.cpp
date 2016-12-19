#include "ui/textentry.h"

#include "autorepeat.h"
#include "keycodes.h"
#include "keymap.h"
#include "keyprocessor.h"
#include "modifierstate.h"
#include "ui/keys.h"
#include "ui/surface.h"

namespace UI
{

bool TextEntry::create(const Types::StrRef& title,
                       const Types::StrRef& text)
{
    mText = text;
    
    mSurface.clear();

    mSurface.paintText(0, 0, title, 0xf, 0);

    mSurface.paintText(0, 20, mText, 0x7, 0);
    mSurface.paintText(mText.size() * 2, 20, "< ", 0x7, 0);

    AutoRepeat autoRepeat;
    ModifierState modifierState;

    bool entered(false);
    
    while (1)
    {
        mKeyProcessor.poll(
            [&](const KeyEvent& event)
            {
                if (!modifierState.processEvent(event))
                {
                    autoRepeat.processEvent(event);
                }
            });

        auto keyId(autoRepeat.activeKey());

        if (Keys::cancel(keyId))
        {
            entered = false;
            break;
        }
        else if (keyId.type() == KeyId::Type::kKey && keyId.value() != 0)
        {
            if (keyId.value() == KeyCodes::Backspace)
            {
                mText.popEnd();
            }
            else if (keyId.value() == KeyCodes::Enter)
            {
                entered = true;
                break;
            }
            else
            {
                if (modifierState.shift())
                {
                    mText.appendChar(KeyMap::getEntry(keyId.value()).shift);
                }
                else
                {
                    mText.appendChar(KeyMap::getEntry(keyId.value()).dflt);                    
                }
            }
            
            mSurface.paintText(0, 20, mText, 0x7, 0);
            mSurface.paintText(mText.size() * 2, 20, "< ", 0x7, 0);
        }
    }

    mSurface.clear();

    return entered;
}

}
