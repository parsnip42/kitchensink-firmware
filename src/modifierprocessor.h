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

private:
    KeyHandler& mKeyHandler;
    ModifierSet mModifierSet;
};

#endif
