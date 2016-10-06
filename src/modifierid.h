#ifndef INCLUDED_MODIFIERID_H
#define INCLUDED_MODIFIERID_H

#include <cstdint>

namespace ModifierId
{

enum Value
{
    kLCtrl  = 0,
    kLShift = 1,
    kLAlt   = 2,
    kLGui   = 3,
    kRCtrl  = 4,
    kRShift = 5,
    kRAlt   = 6,
    kRGui   = 7
};

inline
int Layer(int layerId)
{
    return layerId + 10;
}

}

#endif
