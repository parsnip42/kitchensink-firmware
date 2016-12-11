#include "ui/textentry.h"

#include "autorepeat.h"
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

        if (keyId.type() == KeyId::Type::kKey && keyId.value() != 0)
        {
            text.appendChar(KeyMap::table()[keyId.value()].dflt[0]);
            mSurface.paintText(0, 20, text, 0xf, 0);
        }
        else if (Keys::cancel(keyId))
        {
            break;
        }
    }

    mSurface.clear();
}

}
