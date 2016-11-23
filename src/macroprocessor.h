#ifndef INCLUDED_MACROPROCESSOR_H
#define INCLUDED_MACROPROCESSOR_H

class KeyEvent;
class EventQueue;
class MacroSet;

class MacroProcessor
{
public:
    constexpr MacroProcessor() = default;

public:
    bool processEvent(const MacroSet& macroSet,
                      const KeyEvent& event,
                      EventQueue&     eventQueue);
    
private:
    MacroProcessor(const MacroProcessor&) = delete;
    MacroProcessor& operator=(const MacroProcessor&) = delete;
};

#endif
