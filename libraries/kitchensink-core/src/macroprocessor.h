#ifndef INCLUDED_MACROPROCESSOR_H
#define INCLUDED_MACROPROCESSOR_H

#include "event/eventstage.h"
#include "macro.h"
#include "timer/timermanager.h"

class Event;
class MacroSet;
class SecureMacroSet;
class GlobalConfig;

class MacroProcessor : public EventStage
{
public:
    MacroProcessor(const MacroSet&       macroSet,
                   const SecureMacroSet& secureMacroSet,
                   const GlobalConfig&   globalConfig,
                   TimerManager&                timer,
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
    const GlobalConfig&            mGlobalConfig;
    const Macro*                   mCurrent;
    Macro::Content::const_iterator mBegin;
    Macro::Content::const_iterator mEnd;
    Timer                          mPlaybackTimer;
    EventStage&                    mNext;
    
private:
    MacroProcessor(const MacroProcessor&) = delete;
    MacroProcessor& operator=(const MacroProcessor&) = delete;
};

#endif
