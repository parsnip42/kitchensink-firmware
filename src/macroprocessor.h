#ifndef INCLUDED_MACROPROCESSOR_H
#define INCLUDED_MACROPROCESSOR_H

#include "event/eventstage.h"
#include "macroset.h"
#include "timer.h"

class Event;
class MacroSet;

class MacroProcessor : public EventStage
{
public:
    MacroProcessor(const MacroSet&       macroSet,
                   const SecureMacroSet& secureMacroSet,
                   Timer&                timer,
                   EventStage&           next);

public:
    virtual bool processEvent(const Event& event) override;
                                                                
private:
    void processMacro(const Macro& macro,
                      bool         pressed);
    void playback();
    
private:
    const MacroSet&                mMacroSet;
    const SecureMacroSet&          mSecureMacroSet;
    const Macro*                   mCurrent;
    Macro::Content::const_iterator mBegin;
    Macro::Content::const_iterator mEnd;
    Timer::Handle                  mPlaybackTimer;
    EventStage&                    mNext;
    
private:
    MacroProcessor(const MacroProcessor&) = delete;
    MacroProcessor& operator=(const MacroProcessor&) = delete;
};

#endif
