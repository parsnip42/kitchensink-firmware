#include "macroprocessor.h"
#include "types/range.h"
#include "event/event.h"
#include "event/macroevent.h"
#include "event/delayevent.h"
#include "macro.h"

MacroProcessor::MacroProcessor(const MacroSet& macroSet,
                               const MacroSet& secureMacroSet,
                               Timer&          timer,
                               EventStage&     next)
    : mMacroSet(macroSet)
    , mSecureMacroSet(secureMacroSet)
    , mCurrent(nullptr)
    , mPlaybackTimer(timer.createHandle())
    , mNext(next)
{ }

bool MacroProcessor::processEvent(const Event& event)
{
    if (mPlaybackTimer.matches(event))
    {
        playback();
    }
    else if (event.is<MacroEvent>())
    {
        auto macroEvent(event.get<MacroEvent>());

        processMacro(((macroEvent.type != MacroEvent::Type::kSecure) ?
                      mMacroSet : mSecureMacroSet),
                     macroEvent.macroId,
                     macroEvent.pressed);
                     
    }
    else
    {
        mNext.processEvent(event);
    }

    return true;
}

void MacroProcessor::processMacro(const MacroSet& macroSet,
                                  uint8_t         macroId,
                                  bool            pressed)
{
    if (macroId < macroSet.size())
    {
        const auto& macro(macroSet[macroId]);
        const auto& content(macro.content);

        if (!pressed && macro.type == Macro::Type::kInvert)
        {
            mCurrent = &macro;
            mBegin   = content.end() - 1;
            mEnd     = content.begin() - 1;
                    
            playback();
        }
        else
        {
            if (pressed)
            {
                mCurrent = &macro;
                mBegin   = content.begin();
                mEnd     = content.end();
                    
                playback();
            }
        }
    }
}

void MacroProcessor::playback()
{
    if (mCurrent)
    {
        while (mBegin != mEnd)
        {
            const auto& event(*mBegin);
            auto forward(mBegin < mEnd);
            
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






