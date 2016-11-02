#ifndef INCLUDED_ACTIONCONTEXT_H
#define INCLUDED_ACTIONCONTEXT_H

class ActionContext
{
public:
    constexpr ActionContext(bool nPressed,
                            int  nTaps);

public:
    bool pressed;
    int  taps;
};

inline
constexpr ActionContext::ActionContext(bool nPressed,
                                       int  nTaps)
    : pressed(nPressed)
    , taps(nTaps)
{ }

#endif

