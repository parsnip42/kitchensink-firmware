#ifndef INCLUDED_TEENSYUSBKEYBOARD_H
#define INCLUDED_TEENSYUSBKEYBOARD_H

#include "event/eventstage.h"
#include "data/keycode.h"

#include <cstdint>

class Event;

class TeensyUsbKeyboard : public EventStage
{
public:
    TeensyUsbKeyboard();

public:
    virtual bool processEvent(const Event& event) override;

private:
    void pressKey(KeyCode key);
    void releaseKey(KeyCode key);

private:
    int     mKeyNum;
    uint8_t mKeyMask[256 >> 3];
    bool    mDirty;
    
private:
    TeensyUsbKeyboard(const TeensyUsbKeyboard&) = delete;
    TeensyUsbKeyboard& operator=(const TeensyUsbKeyboard&) = delete;
};

#endif
    
