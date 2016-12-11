#include "ui/textentry.h"

#include "autorepeat.h"
#include "keycodes.h"
#include "keymap.h"
#include "keyprocessor.h"

#include "types/strbuf.h"
#include "ui/keys.h"
#include "ui/surface.h"

namespace UI
{

void TextEntry::create()
{
    mSurface.clear();

    mSurface.paintText(0, 0, mTitle, 0, 0xf);

    Types::StrBuf<30> text;
    
    mSurface.paintText(0, 20, text, 0xf, 0);

    AutoRepeat autoRepeat;

    while (1)
    {
        mKeyProcessor.poll(
            [&](const KeyEvent& event)
            {
                autoRepeat.processEvent(event);
            });

        auto keyId(autoRepeat.activeKey());

        if (Keys::cancel(keyId))
        {
            break;
        }
        else if (keyId.type() == KeyId::Type::kKey && keyId.value() != 0)
        {
            if (keyId.value() == KeyCodes::Backspace)
            {
                text.popEnd();
            }
            else if (keyId.value() == KeyCodes::Enter)
            {
                break;
            }
            else
            {
                text.appendChar(KeyMap::getEntry(keyId.value()).dflt.begin()[0]);
            }
            
            mSurface.paintText(0, 20, text, 0xf, 0);
            mSurface.paintText(text.size()*2, 20, " ", 0xf, 0);
        }
    }

    mSurface.clear();
}

}
