#ifndef INCLUDED_ACTIONPROCESSOR_H
#define INCLUDED_ACTIONPROCESSOR_H

#include "keyevent.h"
#include "eventqueue.h"

#include <array>
#include <functional>

class ActionContext;
class EventQueue;

class ActionProcessor
{
public:
    static constexpr int kMaxActions = 10;
    
public:
    typedef std::function<void(const ActionContext&)> Func;
    
public:
    ActionProcessor() = default;

public:
    bool processEvent(const KeyEvent& event, EventQueue&);
    void registerAction(int action, const Func& func);
    
private:
    void fireAction(int action, const ActionContext& context) const;
    
private:
    std::array<Func, kMaxActions> mActions;

private:
    ActionProcessor(const ActionProcessor&) = delete;
    ActionProcessor& operator=(const ActionProcessor&) = delete;
};

#endif
