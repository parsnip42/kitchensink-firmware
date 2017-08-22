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
    MacroProcessor(const MacroSet& macroSet,
                   Timer&          timer,
                   EventStage&     next);

public:
    virtual void processEvent(const Event& event) override;
                                                                
private:
    void playback();
    
private:
    const MacroSet&                mMacroSet;
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
