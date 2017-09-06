#ifndef INCLUDED_ACTION_H
#define INCLUDED_ACTION_H

class Action
{
public:
    template <typename T, void (T::*MemFunc)()>
    static Action memFn(T* t);

public:
    typedef void(*Func)(void* data);
    
public:
    Action();
    Action(void*       data,
           const Func& func);

public:
    void fireAction();

private:
    void* mData;
    Func  mFunc;
};


template <typename T, void (T::*MemFunc)()>
inline
Action Action::memFn(T* t)
{
    return Action(t, [](void* data)
    {
        (((T*)data)->*MemFunc)();
    });
}


inline
Action::Action()
    : mData(nullptr)
    , mFunc([](void*){})
{ }

inline
Action::Action(void*       data,
               const Func& func)
    : mData(data)
    , mFunc(func)
{ }

inline
void Action::fireAction()
{
    mFunc(mData);
}

#endif
