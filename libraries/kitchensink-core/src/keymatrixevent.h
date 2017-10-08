#ifndef INCLUDED_KEYMATRIXEVENT_H
#define INCLUDED_KEYMATRIXEVENT_H

class KeyMatrixEvent
{
public:
    constexpr KeyMatrixEvent(int  nRow,
                             int  nColumn,
                             bool nPressed);
    
public:
    int  row;
    int  column;
    bool pressed;
};


inline
constexpr KeyMatrixEvent::KeyMatrixEvent(int  nRow,
                                         int  nColumn,
                                         bool nPressed)
    : row(nRow)
    , column(nColumn)
    , pressed(nPressed)
{ }

#endif
