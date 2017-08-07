#ifndef INCLUDED_ACTIONPROCESSOR_H
#define INCLUDED_ACTIONPROCESSOR_H

#include "keyeventstage.h"

#include <array>

class KeyEvent;

class ActionProcessor : public KeyEventStage
{    
public:
    explicit ActionProcessor(KeyEventStage& next);

public:
    virtual void processKeyEvent(const KeyEvent& event) override;
    
private:
    KeyEventStage& mNext;
    
private:
    ActionProcessor(const ActionProcessor&) = delete;
    ActionProcessor& operator=(const ActionProcessor&) = delete;
};

#endif
