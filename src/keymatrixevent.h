#ifndef INCLUDED_KEYMATRIXEVENT_H
#define INCLUDED_KEYMATRIXEVENT_H

class KeyMatrixEvent
{
public:
    enum State
    {
        kNone     = 0,
        kReleased = 1,
        kHeld     = 2,
        kPressed  = 3
    };
    
public:
    KeyMatrixEvent(int   nRow,
                   int   nColumn,
                   State nState);
    
public:
    int   row;
    int   column;
    State state;
};


inline
KeyMatrixEvent::KeyMatrixEvent(int   nRow,
                               int   nColumn,
                               State nState)
    : row(nRow)
    , column(nColumn)
    , state(nState)
{ }

#endif
