#ifndef INCLUDED_ACTIONPROCESSOR_H
#define INCLUDED_ACTIONPROCESSOR_H

#include "keyevent.h"
#include "eventqueue.h"

#include <array>

class EventQueue;
class KeyHandler;

namespace UI { class Surface; };

class ActionProcessor
{
public:
    static constexpr int kMaxActions = 10;
    
public:
    explicit ActionProcessor(KeyHandler&  keyHandler,
                             UI::Surface& surface);

public:
    bool processEvent(const KeyEvent& event,
                      EventQueue&     eventQueue);
    
private:
    void fireBuiltIn(int             action,
                     const KeyEvent& event,
                     EventQueue&     eventQueue) const;
    
    void fireMenu(int             action,
                  const KeyEvent& event,
                  EventQueue&     eventQueue) const;

private:
    KeyHandler&  mKeyHandler;
    UI::Surface& mSurface;

private:
    ActionProcessor(const ActionProcessor&) = delete;
    ActionProcessor& operator=(const ActionProcessor&) = delete;
};

#endif
