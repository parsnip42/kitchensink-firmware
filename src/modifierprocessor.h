#ifndef INCLUDED_MODIFIERPROCESSOR_H
#define INCLUDED_MODIFIERPROCESSOR_H

#include "modifier.h"
#include "modifierid.h"
#include "modifierset.h"
#include "keyhandler.h"

#include <array>

class EventQueue;
class KeyEvent;

class ModifierProcessor
{
public:
    explicit ModifierProcessor(KeyHandler& keyHandler);

public:
    bool processEvent(const KeyEvent& event,
                      EventQueue&     eventQueue);

    const ModifierSet& modifierSet() const;
    ModifierSet& modifierSet();

private:
    KeyHandler& mKeyHandler;
    ModifierSet mModifierSet;
};


inline
const ModifierSet& ModifierProcessor::modifierSet() const
{
    return mModifierSet;
}

inline
ModifierSet& ModifierProcessor::modifierSet()
{
    return mModifierSet;
}

#endif
