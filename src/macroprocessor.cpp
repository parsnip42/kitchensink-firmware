#include "macroprocessor.h"
#include "types/range.h"
#include "keyevent.h"
#include "macro.h"

MacroProcessor::MacroProcessor(const MacroSet& macroSet,
                               Timer&          timer,
                               KeyEventStage&  next)
    : mMacroSet(macroSet)
    , mCurrent(nullptr)
    , mPlaybackTimer(timer.createHandle())
    , mNext(next)
{ }

void MacroProcessor::processKeyEvent(const KeyEvent& event)
{
    const auto& keyId(event.keyId);

    if (mPlaybackTimer.matches(event))
    {
        playback();
    }
    else if (keyId.type() == KeyId::Type::kMacro)
    {
        auto macroIndex(keyId.value());

        if (macroIndex < mMacroSet.size())
        {
            const auto& macro(mMacroSet[keyId.value()]);
            const auto& content(macro.content);

            if (!event.pressed && macro.type == MacroType::kInvert)
            {
                mCurrent = &macro;
                mBegin   = content.end() - 1;
                mEnd     = content.begin() - 1;
                    
                playback();
            }
            else
            {
                if (event.pressed)
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
        mNext.processKeyEvent(event);
    }
}

void MacroProcessor::playback()
{
    if (mCurrent)
    {
        while (mBegin != mEnd)
        {
            bool forward(mBegin < mEnd);
            
            const auto& event(*mBegin);
            
            if (forward)
            {
                ++mBegin;
            }
            else
            {
                --mBegin;
            }
            
            if (event.keyId.type() == KeyId::Type::kDelay)
            {
                mPlaybackTimer.schedule(event.keyId.delayMs());
                return;
            }
            else if (!forward)
            {
                mNext.processKeyEvent(KeyEvent(event.keyId, false));
            }
            else
            {
                mNext.processKeyEvent(event);
            }
        }
        
        mCurrent = nullptr;
    }
}






