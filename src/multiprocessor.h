#ifndef INCLUDED_MULTIPROCESSOR_H
#define INCLUDED_MULTIPROCESSOR_H

#include "multi.h"

#include <array>

class EventQueue;
class KeyEvent;

class MultiProcessor
{
public:
    constexpr MultiProcessor() = default;

public:
    bool processEvent(const KeyEvent& event,
                      EventQueue&     eventQueue);

public:
    void assign(int index, const Multi& multi);
    
private:
    std::array<Multi, 40> mMulti;

private:
    MultiProcessor(const MultiProcessor&) = delete;
    MultiProcessor& operator=(const MultiProcessor&) = delete;
};

#endif
