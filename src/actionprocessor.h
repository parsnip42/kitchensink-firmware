#ifndef INCLUDED_ACTIONPROCESSOR_H
#define INCLUDED_ACTIONPROCESSOR_H

#include "menudefinitions.h"

#include <array>

class KeyEvent;
class KeyProcessor;
class KeyboardState;

namespace UI { class Surface; };

class ActionProcessor
{
public:
    static constexpr int kMaxActions = 10;
    
public:
    explicit ActionProcessor(KeyProcessor&  keyProcessor,
                             KeyboardState& keyboardState,
                             UI::Surface&   surface);

public:
    bool processEvent(const KeyEvent& event);
    
private:
    void fireBuiltIn(int             action,
                     const KeyEvent& event) const;
    
    void fireMenu(int             action,
                  const KeyEvent& event) const;

    void fireEdit() const;

private:
    KeyProcessor&   mKeyProcessor;
    KeyboardState&  mKeyboardState;
    UI::Surface&    mSurface;
    MenuDefinitions mMenuDefinitions;
    
private:
    ActionProcessor(const ActionProcessor&) = delete;
    ActionProcessor& operator=(const ActionProcessor&) = delete;
};

#endif
