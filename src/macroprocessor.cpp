#include "macroprocessor.h"
#include "types/range.h"
#include "event/event.h"
#include "event/macroevent.h"
#include "event/delayevent.h"
#include "macro.h"

MacroProcessor::MacroProcessor(const MacroSet& macroSet,
                               Timer&          timer,
                               EventStage&     next)
    : mMacroSet(macroSet)
    , mCurrent(nullptr)
    , mPlaybackTimer(timer.createHandle())
    , mNext(next)
{ }

void MacroProcessor::processEvent(const Event& event)
{
    if (mPlaybackTimer.matches(event))
    {
        playback();
    }
    else if (event.is<MacroEvent>())
    {
        auto macroEvent(event.get<MacroEvent>());
        auto macroId(macroEvent.macroId);

        if (macroId < mMacroSet.size())
        {
            const auto& macro(mMacroSet[macroId]);
            const auto& content(macro.content);

            if (!macroEvent.pressed && macro.type == MacroType::kInvert)
            {
                mCurrent = &macro;
                mBegin   = content.end() - 1;
                mEnd     = content.begin() - 1;
                    
                playback();
            }
            else
            {
                if (macroEvent.pressed)
                {
                    mCurrent = &macro;
                    mBegin   = content.begin();
                    mEnd     = content.end();
                    
                    playback();
                }
            }
        }
    }
    else
    {
        mNext.processEvent(event);
    }
}

void MacroProcessor::playback()
{
    if (mCurrent)
    {
        while (mBegin != mEnd)
        {
            const auto& event(*mBegin);
            
            bool forward(mBegin < mEnd);
            
            if (forward)
            {
                ++mBegin;
            }
            else
            {
                --mBegin;
            }
            
            if (event.is<DelayEvent>())
            {
                mPlaybackTimer.schedule(event.get<DelayEvent>().delayMs);
                return;
            }
            else
            {
                mNext.processEvent(forward ? event : event.invert());
            }
        }
        
        mCurrent = nullptr;
    }
}






