#include "ui/recordmacro.h"

#include "keyprocessor.h"
#include "usbkeyboard.h"
#include "ui/surface.h"

#include <elapsedMillis.h>
#include <cstdint>

namespace UI
{

bool RecordMacro::create(const Types::StrRef& title,
                         bool                 realtime)
{
    mSurface.clear();

    mSurface.paintText(0, 0, title, 0xf, 0);

    bool quit(false);

    uint32_t lastMs(0);

    Types::StrBuf<30> macroText;

    mKeyProcessor.untilIdle();

    while (!quit)
    {
        mKeyProcessor.poll(
            [&](const KeyEvent& event)
            {
                const auto& keyId(event.keyId);

                if (keyId == KeyId::Action(KeyId::ActionType::kMenu, 0))
                {
                    if (!event.pressed)
                    {
                        quit = true;
                    }
                    
                    return;
                }
                
                if (keyId.type() == KeyId::Type::kKey)
                {
                    mUsbKeyboard.processKey(keyId.value(), event.pressed);
                }

                if (mMacroSize < mMacro.size() - 1)
                {
                    if (realtime)
                    {
                        auto nowMs(millis());
                        
                        if (lastMs != 0)
                        {
                            mMacro[mMacroSize++] = KeyEvent(KeyId::Delay(nowMs - lastMs));    
                        }
                        
                        lastMs = nowMs;
                    }

                    mMacro[mMacroSize++] = event;
                }
                else
                {
                    mSurface.paintText(0, 40, "Macro Full", 0xf, 0);
                }
                
                Types::StrBuf<30> text;

                text.appendInt(mMacroSize)
                    .appendStr(" events");
                
                mSurface.paintText(0, 20, text, 0x7, 0);
            });
    }
    
    mSurface.clear();

    return true;
}

}
