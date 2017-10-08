#ifndef INCLUDED_ARDUINOUSBKEYBOARD_H
#define INCLUDED_ARDUINOUSBKEYBOARD_H

#include "event/eventstage.h"
#include "data/keycode.h"

#include <cstdint>

class Event;

class ArduinoUsbKeyboard : public EventStage
{
private:
    struct KeyReport
    {
        uint8_t modifiers;
        uint8_t reserved;
        uint8_t keys[6];
    };

public:
    ArduinoUsbKeyboard();

public:
    virtual bool processEvent(const Event& event) override;

private:
    void pressKey(KeyCode key);
    void releaseKey(KeyCode key);

private:
    int       mKeyNum;
    uint8_t   mKeyMask[256 >> 3];
    bool      mDirty;
    KeyReport mKeyReport;
    
private:
    ArduinoUsbKeyboard(const ArduinoUsbKeyboard&) = delete;
    ArduinoUsbKeyboard& operator=(const ArduinoUsbKeyboard&) = delete;
};

#endif
