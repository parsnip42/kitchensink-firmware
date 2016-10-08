#ifndef INCLUDED_KEYMATRIXEVENT_H
#define INCLUDED_KEYMATRIXEVENT_H

#include "keystate.h"

class KeyMatrixEvent
{
public:
    KeyMatrixEvent(int      nRow,
                   int      nColumn,
                   KeyState nState);
    
public:
    int      row;
    int      column;
    KeyState state;
};


inline
KeyMatrixEvent::KeyMatrixEvent(int      nRow,
                               int      nColumn,
                               KeyState nState)
    : row(nRow)
    , column(nColumn)
    , state(nState)
{ }

#endif
