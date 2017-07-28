#include "ui/recordmacroscreen.h"

#include "keyprocessor.h"
#include "macro.h"
#include "ui/surface.h"
#include "types/strostream.h"
#include "keyeventrecorder.h"
#include "eventmanager.h"

#include <cstdint>


void RecordMacroScreen::poll()
{
    redraw();
    
    while (!mRecorder.complete())
    {
        mEventManager.poll(*this);
    }
}

void RecordMacroScreen::redraw()
{
    mSurface.clear();

    mSurface.paintText(0, 0, "Macro", 0xf, 0);

    if (!mRecorder.full())
    {
        StrBuf<30> text;
        StrOStream ostream(text);
        
        ostream.appendInt(mRecorder.size())
                         .appendStr(" events");
            
        mSurface.paintText(0, 20, text, 0x7, 0);
    }
    else
    {
        mSurface.paintText(0, 40, "Macro Full", 0xf, 0);
    }
}

void RecordMacroScreen::processKeyEvent(const KeyEvent& event)
{
    mEventManager.defaultOutput.processKeyEvent(event);
    mRecorder.processKeyEvent(event);

    if (!mRecorder.full())
    {
        StrBuf<30> text;
        StrOStream ostream(text);
                
        ostream.appendInt(mRecorder.size())
               .appendStr(" events");
            
        mSurface.paintText(0, 20, text, 0x7, 0);
    }
    else
    {
        mSurface.paintText(0, 40, "Macro Full", 0xf, 0);
    }

    if (mRecorder.complete())
    {
        mMacro.content.assign(mRecorder.begin(),
                              mRecorder.end());
    }
}