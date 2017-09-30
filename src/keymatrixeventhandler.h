#ifndef INCLUDED_KEYMATRIXEVENTHANDLER_H
#define INCLUDED_KEYMATRIXEVENTHANDLER_H

class KeyMatrixEvent;

class KeyMatrixEventHandler
{
private:
    template <typename Func>
    class Impl;
    
public:
    virtual void processKeyMatrixEvent(const KeyMatrixEvent& event) const = 0;

public:
    template <typename Func>
    static Impl<Func> create(const Func& func);
};


template <typename Func>
class KeyMatrixEventHandler::Impl : public KeyMatrixEventHandler
{
public:
    explicit Impl(const Func& func);

public:
    virtual void processKeyMatrixEvent(const KeyMatrixEvent& event) const;
            
private:
    Func mFunc;
};


template <typename Func>
inline
KeyMatrixEventHandler::Impl<Func>::Impl(const Func& func)
    : mFunc(func)
{ }

template <typename Func>
inline
void KeyMatrixEventHandler::Impl<Func>::processKeyMatrixEvent(const KeyMatrixEvent& event) const
{
    mFunc(event);
}


template <typename Func>
inline
KeyMatrixEventHandler::Impl<Func> KeyMatrixEventHandler::create(const Func& func)
{
    return KeyMatrixEventHandler::Impl<Func>(func);
}

#endif
