#include "ui/recordmacroscreen.h"

#include "macro.h"
#include "ui/surface.h"
#include "types/strostream.h"
#include "keyeventrecorder.h"
#include "eventmanager.h"
#include "storage/storage.h"
#include "serialize/serializer.h"
#include "screenstack.h"

#include <cstdint>

RecordMacroScreen::RecordMacroScreen(ScreenStack&   screenStack,
                                     Timer&         timer,
                                     MacroSet&      macroSet,
                                     int            macroId,
                                     bool           realtime,
                                     KeyEventStage& next)
    : mScreenStack(screenStack)
    , mMacroSet(macroSet)
    , mMacroId(macroId)
    , mRecorder(realtime)
    , mLabelWidget("Recording",
                   Justify::kCenter)
    , mFlashTimer(timer.createHandle())
    , mFlash(true)
    , mNext(next)
{
    mFlashTimer.scheduleRepeating(500, 500);
}

void RecordMacroScreen::processKeyEvent(const KeyEvent& event)
{
    if (mFlashTimer.matches(event))
    {
        mFlash = !mFlash;

        if (mRecorder.full())
        {
            mLabelWidget.text = "Macro Storage Full";
            mFlashTimer.cancel();
        }
        else
        {
            mLabelWidget.text = mFlash ? "Recording" : "";
        }
        
        mLabelWidget.invalidateWidget();
        return;
    }

    mNext.processKeyEvent(event);
    mRecorder.processKeyEvent(event);

    if (mRecorder.complete())
    {
        auto& macro(mMacroSet[mMacroId]);
        
        macro.content.assign(mRecorder.begin(),
                             mRecorder.end());

        Storage storage;
        Serializer<MacroSet> s;
                
        auto os(storage.write(Storage::Region::Macro));
                
        s.serialize(mMacroSet, os);

        mScreenStack.pop();
    }
}

Widget& RecordMacroScreen::rootWidget()
{
    return mLabelWidget;
}
