#include "ui/recordmacroscreen.h"

#include "macro.h"
#include "macroset.h"
#include "ui/surface.h"
#include "eventrecorder.h"
#include "eventmanager.h"
#include "event/event.h"
#include "event/screenevent.h"
#include "keyboardstateutil.h"

#include <cstdint>

RecordMacroScreen::RecordMacroScreen(Timer&      timer,
                                     MacroSet&   macroSet,
                                     int         macroId,
                                     EventStage& next)
    : mMacroSet(macroSet)
    , mMacroId(macroId)
    , mRecorder(mMacroSet[macroId].type == Macro::Type::kRealtime)
    , mLabelWidget("Recording",
                   Justify::kCenter)
    , mFlashTimer(timer.createHandle())
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
            auto& macro(mMacroSet[mMacroId]);
            
            macro.content.assign(mRecorder.begin(),
                                 mRecorder.end());
            
            KeyboardStateUtil::store(mMacroSet);
            
            mNext.processEvent(ScreenEvent::create(ScreenEvent::Type::kHome, 0));
        }

        return processed;
    }
    
    return true;
}

Widget& RecordMacroScreen::rootWidget()
{
    return mLabelWidget;
}
