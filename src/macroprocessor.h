#ifndef INCLUDED_MACROPROCESSOR_H
#define INCLUDED_MACROPROCESSOR_H

#include "keyeventstage.h"
#include "macroset.h"

class KeyEvent;
class MacroSet;

class MacroProcessor : public KeyEventStage
{
public:
    MacroProcessor(const MacroSet& macroSet,
                   KeyEventStage&  next);

public:
    virtual void processKeyEvent(const KeyEvent& event) override;

private:
    const MacroSet& mMacroSet;
    KeyEventStage&  mNext;
    
private:
    MacroProcessor(const MacroProcessor&) = delete;
    MacroProcessor& operator=(const MacroProcessor&) = delete;
};


inline
MacroProcessor::MacroProcessor(const MacroSet& macroSet,
                               KeyEventStage&  next)
    : mMacroSet(macroSet)
    , mNext(next)
{ }

#endif
