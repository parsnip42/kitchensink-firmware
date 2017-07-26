#ifndef INCLUDED_ACTIONPROCESSOR_H
#define INCLUDED_ACTIONPROCESSOR_H

#include "menudefinitions.h"
#include "usbkeyboard.h"
#include "keyeventstage.h"

#include <array>

class KeyEvent;
class KeyProcessor;
class KeyboardState;
class Surface;

class ActionProcessor : public KeyEventStage
{
public:
    static constexpr int kMaxActions = 10;
    
public:
    ActionProcessor(KeyboardState& keyboardState,
                    Surface&       surface,
                    KeyEventStage& next);

public:
    virtual void processKeyEvent(const KeyEvent& event) override;
    
private:
    void fireBuiltIn(int             action,
                     const KeyEvent& event) const;
    
    void fireMenu(int             action,
                  const KeyEvent& event) const;

    void fireEdit() const;

private:
    KeyboardState&  mKeyboardState;
    Surface&        mSurface;
    MenuDefinitions mMenuDefinitions;
    KeyEventStage&  mNext;
    
private:
    ActionProcessor(const ActionProcessor&) = delete;
    ActionProcessor& operator=(const ActionProcessor&) = delete;
};

#endif
