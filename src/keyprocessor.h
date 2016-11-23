#ifndef INCLUDED_KEYPROCESSOR_H
#define INCLUDED_KEYPROCESSOR_H

#include "eventqueue.h"
#include "macroprocessor.h"
#include "modifierprocessor.h"
#include "profile.h"

class KeyDispatcher;

class KeyProcessor
{
public:
    explicit KeyProcessor(KeyDispatcher& keyDispatcher);

public:
    void poll();
    bool hasEvent();
    KeyEvent popEvent();
    
private:
    KeyDispatcher&    mKeyDispatcher;
    Profile           mProfile;
    EventQueue        mEventQueue;
    ModifierProcessor mModifierProcessor;
    MacroProcessor    mMacroProcessor;
    
private:
    KeyProcessor(const KeyProcessor&) = delete;
    KeyProcessor& operator=(const KeyProcessor&) = delete;
};

#endif
