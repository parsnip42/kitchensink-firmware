#ifndef INCLUDED_UI_H
#define INCLUDED_UI_H

#include "eventqueue.h"

class Display;
class KeyHandler;

class UI
{
public:
    explicit UI(Display& display);

public:
    void menu(KeyHandler& keyHandler, EventQueue& eventQueue);
    void paintText(int x, int y, const char* str);
    void paintText(int x, int y, const char* str, bool inv, uint8_t fg = 0xf, uint8_t bg = 0);
    void clear();

private:
    Display& mDisplay;
    
private:
    UI(const UI&) = delete;
    UI& operator=(const UI&) = delete;
};

#endif
