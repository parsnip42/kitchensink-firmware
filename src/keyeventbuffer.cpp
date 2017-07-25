#include "keyeventbuffer.h"

void KeyEventBuffer::processKeyEvent(const KeyEvent& event)
{
    mBuffer.pushBack(event);
}
