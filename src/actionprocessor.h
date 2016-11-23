#ifndef INCLUDED_ACTIONPROCESSOR_H
#define INCLUDED_ACTIONPROCESSOR_H

#include <array>

class KeyEvent;
class KeyProcessor;

namespace UI { class Surface; };

class ActionProcessor
{
public:
    static constexpr int kMaxActions = 10;
    
public:
    explicit ActionProcessor(KeyProcessor& keyProcessor,
                             UI::Surface&  surface);

public:
    bool processEvent(const KeyEvent& event);
    
private:
    void fireBuiltIn(int             action,
                     const KeyEvent& event) const;
    
    void fireMenu(int             action,
                  const KeyEvent& event) const;

private:
    KeyProcessor& mKeyProcessor;
    UI::Surface&   mSurface;

private:
    ActionProcessor(const ActionProcessor&) = delete;
    ActionProcessor& operator=(const ActionProcessor&) = delete;
};

#endif
