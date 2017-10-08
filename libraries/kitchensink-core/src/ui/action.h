#ifndef INCLUDED_ACTION_H
#define INCLUDED_ACTION_H

class Action
{
public:
    template <typename T, void (T::*MemFunc)()>
    static Action memFn(T* t);

    static Action action(Action& action);

    static Action trigger(bool& value);

public:
    typedef bool(*Func)(void* data);

public:
    Action();
    
private:
    Action(void*       data,
           const Func& func);

public:
    bool fireAction();

private:
    void* mData;
    Func  mFunc;
};


template <typename T, void (T::*MemFunc)()>
inline
Action Action::memFn(T* t)
{
    return Action(t, [](void* data) -> bool
    {
        ((reinterpret_cast<T*>(data))->*MemFunc)();

        return true;
    });
}

inline
Action Action::action(Action& action)
{
    return Action(&action, [](void* data) -> bool
    {
        return (reinterpret_cast<Action*>(data))->fireAction();
    });
}

#endif










