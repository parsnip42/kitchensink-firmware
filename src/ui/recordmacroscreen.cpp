#include "ui/recordmacroscreen.h"

#include "macro.h"
#include "ui/surface.h"
#include "types/strostream.h"
#include "eventrecorder.h"
#include "eventmanager.h"
#include "storage/storage.h"
#include "serialize/serializer.h"
#include "event/event.h"
#include "event/screenevent.h"

#include <cstdint>

RecordMacroScreen::RecordMacroScreen(Timer&      timer,
                                     MacroSet&   macroSet,
                                     int         macroId,
                                     bool        realtime,
                                     EventStage& next)
    : mMacroSet(macroSet)
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
        mNext.processEvent(event);
        mRecorder.processEvent(event);
        
        if (mRecorder.complete())
        {
            auto& macro(mMacroSet[mMacroId]);
            
            macro.content.assign(mRecorder.begin(),
                                 mRecorder.end());
            
            Storage storage;
            Serializer<MacroSet> s;
            
            auto os(storage.write(Storage::Region::Macro));
            
            s.serialize(mMacroSet, os);
            
            mNext.processEvent(ScreenEvent::create(ScreenEvent::Type::kHome, 0));
        }
    }
    
    return true;
}

Widget& RecordMacroScreen::rootWidget()
{
    return mLabelWidget;
}
