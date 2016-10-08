#ifndef INCLUDED_ACTIONCONTEXT_H
#define INCLUDED_ACTIONCONTEXT_H

#include "keystate.h"

class ActionContext
{
public:
    ActionContext(KeyState nState,
                  int      nTaps);

public:
    KeyState state;
    int      taps;
};

inline
ActionContext::ActionContext(KeyState nState,
                             int      nTaps)
    : state(nState)
    , taps(nTaps)
{ }

#endif

