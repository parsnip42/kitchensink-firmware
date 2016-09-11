#ifndef INCLUDED_ACTIONMANAGER_H
#define INCLUDED_ACTIONMANAGER_H

#include <array>
#include <functional>

class ActionContext;

class ActionManager
{
public:
    static const int kMaxActions = 10;
    
public:
    typedef std::function<void(const ActionContext&)> Func;
    
public:
    ActionManager();

public:
    void fireAction(int action, const ActionContext& context) const;
    void registerAction(int action, const Func& func);

private:
    std::array<Func, kMaxActions> mActions;

private:
    ActionManager(const ActionManager&) = delete;
    ActionManager& operator=(const ActionManager&) = delete;
};

#endif
