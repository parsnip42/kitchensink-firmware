#include "macroprocessor.h"
#include "types/range.h"
#include "event/event.h"
#include "event/macroevent.h"
#include "event/delayevent.h"
#include "event/screenevent.h"
#include "macro.h"

MacroProcessor::MacroProcessor(const MacroSet&       macroSet,
                               const SecureMacroSet& secureMacroSet,
                               Timer&                timer,
                               EventStage&           next)
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
        auto macroId(macroEvent.macroId);
        
        switch (macroEvent.type)
        {
        case MacroEvent::Type::kDefault:
            if (macroId < mMacroSet.size())
            {
                processMacro(mMacroSet[macroId],
                             macroEvent.pressed);
            }
            break;

        case MacroEvent::Type::kSecure:
            if (mSecureMacroSet.unlocked())
            {
                if (macroId < mSecureMacroSet.size())
                {
                    processMacro(mSecureMacroSet[macroId],
                                 macroEvent.pressed);
                }
            }
            else if (macroEvent.pressed)
            {
                mNext.processEvent(ScreenEvent::create(ScreenEvent::Type::kScreen, ScreenEvent::kMacroUnlock));
            }
            break;
        }
    }
    else
    {
        mNext.processEvent(event);
    }

    return true;
}

void MacroProcessor::processMacro(const Macro& macro,
                                  bool         pressed)
{
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






