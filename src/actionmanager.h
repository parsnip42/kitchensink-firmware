#ifndef INCLUDED_ACTIONMANAGER_H
#define INCLUDED_ACTIONMANAGER_H

#include "keyevent.h"
#include "eventqueue.h"

#include <array>
#include <functional>

class ActionContext;
class EventQueue;

class ActionManager
{
public:
    static constexpr int kMaxActions = 10;
    
public:
    typedef std::function<void(const ActionContext&)> Func;
    
public:
    ActionManager() = default;

public:
    bool processEvent(const KeyEvent& event, EventQueue&);
    void registerAction(int action, const Func& func);
    
private:
    void fireAction(int action, const ActionContext& context) const;
    
private:
    std::array<Func, kMaxActions> mActions;

private:
    ActionManager(const ActionManager&) = delete;
    ActionManager& operator=(const ActionManager&) = delete;
};

#endif
