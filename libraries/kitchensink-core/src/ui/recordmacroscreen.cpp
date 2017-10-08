#include "ui/recordmacroscreen.h"

#include "macro.h"
#include "macroset.h"
#include "ui/surface.h"
#include "eventrecorder.h"
#include "eventmanager.h"
#include "event/event.h"
#include "event/screenevent.h"

#include <cstdint>

RecordMacroScreen::RecordMacroScreen(TimerManager&      timer,
                                     Macro&      macro,
                                     EventStage& next)
    : mMacro(macro)
    , mRecorder(macro.type == Macro::Type::kRealtime)
    , mLabelWidget("Recording",
                   Justify::kCenter)
    , mFlashTimer(timer.createTimer())
    , mFlash(true)
    , mNext(next)
{
    mFlashTimer.scheduleRepeating(500, 500);
}

bool RecordMacroScreen::processEvent(const Event& event)
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
    }
    else
    {
        auto processed(mNext.processEvent(event));
        
        mRecorder.processEvent(event);
        
        if (mRecorder.complete())
        {
            mMacro.content.assign(mRecorder.begin(),
                                  mRecorder.end());

            screenCompleted.fireAction();
        }

        return processed;
    }
    
    return true;
}

Widget& RecordMacroScreen::rootWidget()
{
    return mLabelWidget;
}
