#ifndef INCLUDED_MODIFIERPROCESSOR_H
#define INCLUDED_MODIFIERPROCESSOR_H

#include "modifierset.h"
#include "tapping.h"

class EventQueue;
class KeyEvent;

class ModifierProcessor
{
public:
    constexpr ModifierProcessor();

public:
    bool processEvent(ModifierSet&    modifierSet,
                      const KeyEvent& event,
                      EventQueue&     eventQueue);

private:
    Tapping mTapping;
};


inline
constexpr ModifierProcessor::ModifierProcessor()
    : mTapping(500)
{ }

#endif
