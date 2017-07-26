#ifndef INCLUDED_ACTIONPROCESSOR_H
#define INCLUDED_ACTIONPROCESSOR_H

#include "menudefinitions.h"
#include "usbkeyboard.h"
#include "keyeventstage.h"

#include <array>

class KeyEvent;
class KeyboardState;

class ActionProcessor : public KeyEventStage
{    
public:
    ActionProcessor(KeyboardState& keyboardState,
                    KeyEventStage& next);

public:
    virtual void processKeyEvent(const KeyEvent& event) override;
    
private:
    void fireBuiltIn(int             action,
                     const KeyEvent& event) const;
    
private:
    KeyboardState& mKeyboardState;
    KeyEventStage& mNext;
    
private:
    ActionProcessor(const ActionProcessor&) = delete;
    ActionProcessor& operator=(const ActionProcessor&) = delete;
};

#endif
