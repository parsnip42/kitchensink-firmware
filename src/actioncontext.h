#ifndef INCLUDED_ACTIONCONTEXT_H
#define INCLUDED_ACTIONCONTEXT_H

class ActionContext
{
public:
    ActionContext(bool nPressed,
                  int  nTaps);

public:
    bool pressed;
    int  taps;
};

inline
ActionContext::ActionContext(bool nPressed,
                             int  nTaps)
    : pressed(nPressed)
    , taps(nTaps)
{ }

#endif

