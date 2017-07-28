#include "macroprocessor.h"
#include "types/range.h"
#include "keyevent.h"
#include "macro.h"

MacroProcessor::MacroProcessor(const MacroSet& macroSet,
                               Timer&          timer,
                               KeyEventStage&  next)
    : mMacroSet(macroSet)
    , mTimer(timer)
    , mCurrent(nullptr)
    , mPlaybackTimer()
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
            if (!event.pressed && mMacroSet[macroIndex].type == MacroType::kInvert)
            {
                auto content(mMacroSet[macroIndex].content);
                
                Range<Macro::Content::const_iterator> range(content.begin(), content.end());
                
                for (auto event : range.reverse())
                {
                    event.pressed = !event.pressed;
                    mNext.processKeyEvent(event);
                }
            }
            else
            {
                if (event.pressed)
                {
                    mCurrent = &mMacroSet[keyId.value()];
                    
                    const auto& macro(mMacroSet[keyId.value()]);
                    const auto& content(macro.content);
                    
                    mBegin = content.begin();
                    mEnd = content.end();
                    
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
            const auto& event(*mBegin);
            
            if (event.keyId.type() == KeyId::Type::kDelay)
            {
                ++mBegin;
                
                mPlaybackTimer = mTimer.schedule(event.keyId.delayMs());
                return;
            }
            else
            {
                mNext.processKeyEvent(event);
                ++mBegin;
            }
        }
        
        mCurrent = nullptr;
    }
}






