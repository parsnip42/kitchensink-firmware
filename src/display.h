#ifndef INCLUDED_DISPLAY_H
#define INCLUDED_DISPLAY_H

class Display
{
public:
    Display();

public:
    void init();
    void paint(int x, int y, const char* str);
    void clear();
};

#endif
