#ifndef INCLUDED_MACROPROCESSOR_H
#define INCLUDED_MACROPROCESSOR_H

#include "macroset.h"

class KeyEvent;
class EventQueue;

class MacroProcessor
{
public:
    MacroProcessor();

public:
    bool processEvent(const KeyEvent& event,
                      EventQueue&     eventQueue);
    
private:
    MacroSet mMacroSet;
    
private:
    MacroProcessor(const MacroProcessor&) = delete;
    MacroProcessor& operator=(const MacroProcessor&) = delete;
};

#endif
