#ifndef INCLUDED_KEYHARDWAREEVENTHANDLER_H
#define INCLUDED_KEYHARDWAREEVENTHANDLER_H

class KeyHardwareEvent;

class KeyHardwareEventHandler
{
private:
    template <typename Func>
    class Impl;
    
public:
    virtual void processKeyHardwareEvent(const KeyHardwareEvent& event) const = 0;

public:
    template <typename Func>
    static Impl<Func> create(const Func& func);
};


template <typename Func>
class KeyHardwareEventHandler::Impl : public KeyHardwareEventHandler
{
public:
    explicit Impl(const Func& func);

public:
    virtual void processKeyHardwareEvent(const KeyHardwareEvent& event) const;
            
private:
    Func mFunc;
};


template <typename Func>
inline
KeyHardwareEventHandler::Impl<Func>::Impl(const Func& func)
    : mFunc(func)
{ }

template <typename Func>
inline
void KeyHardwareEventHandler::Impl<Func>::processKeyHardwareEvent(const KeyHardwareEvent& event) const
{
    mFunc(event);
}


template <typename Func>
inline
KeyHardwareEventHandler::Impl<Func> KeyHardwareEventHandler::create(const Func& func)
{
    return KeyHardwareEventHandler::Impl<Func>(func);
}

#endif
