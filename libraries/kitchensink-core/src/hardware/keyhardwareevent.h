#ifndef INCLUDED_KEYHARDWAREEVENT_H
#define INCLUDED_KEYHARDWAREEVENT_H

class KeyHardwareEvent
{
public:
    constexpr KeyHardwareEvent(int  nRow,
                               int  nColumn,
                               bool nPressed);
    
public:
    int  row;
    int  column;
    bool pressed;
};


inline
constexpr KeyHardwareEvent::KeyHardwareEvent(int  nRow,
                                             int  nColumn,
                                             bool nPressed)
    : row(nRow)
    , column(nColumn)
    , pressed(nPressed)
{ }

#endif
