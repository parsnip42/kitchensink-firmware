#include "ui/recordmacro.h"

#include "keyprocessor.h"
#include "macro.h"
#include "ui/surface.h"
#include "types/strostream.h"
#include "keyeventrecorder.h"

#include <cstdint>

bool RecordMacro::create(const StrRef& title,
                         Macro&        macro,
                         bool          realtime)
{
    mSurface.clear();

    mSurface.paintText(0, 0, title, 0xf, 0);

    mKeyProcessor.untilIdle();

    KeyEventRecorder recorder(realtime, mNext);

    while (!recorder.complete())
    {
        // mKeyProcessor.poll(recorder);
        
        if (!recorder.full())
        {
            StrBuf<30> text;
            StrOStream ostream(text);
                
            ostream.appendInt(recorder.size())
                   .appendStr(" events");
            
            mSurface.paintText(0, 20, text, 0x7, 0);
        }
        else
        {
            mSurface.paintText(0, 40, "Macro Full", 0xf, 0);
        }
    }

    macro.content.assign(recorder.begin(),
                         recorder.end());
    
    mSurface.clear();

    return true;
}
