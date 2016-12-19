#include "ui/recordmacro.h"

#include "keyprocessor.h"
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

    std::size_t macroSize(0);

    bool quit(false);

    uint32_t lastMs(0);
    
    while (!quit)
    {
        mKeyProcessor.poll(
            [&](const KeyEvent& event)
            {
                if (event.keyId == KeyId::Action(KeyId::ActionType::kMenu, 0))
                {
                    if (!event.pressed)
                    {
                        quit = true;
                    }
                    
                    return;
                }
                
                if (macroSize < mMacro.size() - 1)
                {
                    auto nowMs(millis());
                    
                    if (lastMs != 0)
                    {
                        mMacro[macroSize++] = KeyEvent(KeyId::Delay(nowMs - lastMs));    
                    }
                    
                    lastMs = nowMs;
                    
                    mMacro[macroSize++] = event;
                }
                else
                {
                    mSurface.paintText(0, 40, "Macro Full", 0xf, 0);
                }
                
                Types::StrBuf<30> text;

                text.appendInt(macroSize)
                    .appendStr(" events");
                
                mSurface.paintText(0, 20, text, 0x7, 0);
            });
    }
    
    mSurface.clear();

    return true;
}

}
