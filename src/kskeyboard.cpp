#include "kskeyboard.h"

KsKeyboard::KsKeyboard()
    : mLeft(0x20, 0x7C00, 0x3FF,
            {{4,3,2,1,0}},
            {{0,1,2,3,4,5,6,7,9,8,10,11,12,13,14,15}})
    , mRight(0x21, 0x3E00, 0xC0FF,
             {{0,1,2,3,4}},
             {{12,13,14,15,16,17,18,19,20,21,22,23,24,25,11,10}})
{ }

void KsKeyboard::init()
{
    mLeft.init();
    mRight.init();
}
