#ifndef INCLUDED_MACROPROCESSOR_H
#define INCLUDED_MACROPROCESSOR_H

#include "keyeventstage.h"
#include "macroset.h"
#include "timer.h"

class KeyEvent;
class MacroSet;

class MacroProcessor : public KeyEventStage
{
public:
    MacroProcessor(Timer&          timer,
                   const MacroSet& macroSet,
                   KeyEventStage&  next);

public:
    virtual void processKeyEvent(const KeyEvent& event) override;
                                                                
private:
    void playback();
    
private:
    Timer&                         mTimer;
    const MacroSet&                mMacroSet;
    const Macro*                   mCurrent;
    Macro::Content::const_iterator mBegin;
    Macro::Content::const_iterator mEnd;
    Timer::Handle                  mPlaybackTimer;
    KeyEventStage&                 mNext;
    
private:
    MacroProcessor(const MacroProcessor&) = delete;
    MacroProcessor& operator=(const MacroProcessor&) = delete;
};


inline
MacroProcessor::MacroProcessor(Timer&          timer,
                               const MacroSet& macroSet,
                               KeyEventStage&  next)
    : mTimer(timer)
    , mMacroSet(macroSet)
    , mCurrent(nullptr)
    , mPlaybackTimer()
    , mNext(next)
{ }

#endif
