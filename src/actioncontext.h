#ifndef INCLUDED_ACTIONCONTEXT_H
#define INCLUDED_ACTIONCONTEXT_H

#include "keystate.h"

class ActionContext
{
public:
    ActionContext(KeyState::Value nState,
                  int             nTaps);

public:
    KeyState::Value state;
    int             taps;
};

inline
ActionContext::ActionContext(KeyState::Value nState,
                             int             nTaps)
    : state(nState)
    , taps(nTaps)
{ }

#endif

