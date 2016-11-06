#ifndef INCLUDED_MACROPROCESSOR_H
#define INCLUDED_MACROPROCESSOR_H

#include "arraypool.h"
#include "macroelement.h"
#include "keyevent.h"

#include <array>

class EventQueue;

class MacroProcessor
{
public:
    MacroProcessor();

public:
    bool processEvent(const KeyEvent& event,
                      EventQueue&     eventQueue);
    
private:
    ArrayPool<std::array<MacroElement, 1024>, 10> mMacroSet;

private:
    MacroProcessor(const MacroProcessor&) = delete;
    MacroProcessor& operator=(const MacroProcessor&) = delete;
};

#endif
