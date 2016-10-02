#ifndef INCLUDED_UI_H
#define INCLUDED_UI_H

class Display;
class KsKeyboard;

class UI
{
public:
    explicit UI(Display& display);

public:
    void menu(KsKeyboard& keyboard);
    void paintText(int x, int y, const char* str);
    void clear();

private:
    Display& mDisplay;
    
private:
    UI(const UI&) = delete;
    UI& operator=(const UI&) = delete;
};

#endif
