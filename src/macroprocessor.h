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
    MacroProcessor(KeyId::Type     macroKeyType,
                   const MacroSet& macroSet,
                   Timer&          timer,
                   KeyEventStage&  next);

public:
    virtual void processKeyEvent(const KeyEvent& event) override;
                                                                
private:
    void playback();
    
private:
    KeyId::Type                    mMacroKeyType;
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

#endif
