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
    MacroProcessor(const MacroSet& macroSet,
                   Timer&          timer,
                   KeyEventStage&  next);

public:
    virtual void processKeyEvent(const KeyEvent& event) override;
                                                                
private:
    void playback();
    
private:
    const MacroSet&                mMacroSet;
    Timer&                         mTimer;
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
MacroProcessor::MacroProcessor(const MacroSet& macroSet,
                               Timer&          timer,
                               KeyEventStage&  next)
    : mMacroSet(macroSet)
    , mTimer(timer)
    , mCurrent(nullptr)
    , mPlaybackTimer()
    , mNext(next)
{ }

#endif
