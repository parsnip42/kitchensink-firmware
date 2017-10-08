#ifndef INCLUDED_DMOLED32DISPLAY_H
#define INCLUDED_DMOLED32DISPLAY_H

// #include "hardware/display.h"
#include <cstdint>

class DMOLED32Display
{
public:
    DMOLED32Display();

public:
    void init();
    void clear();
    
    // int width();
    // int height();

    template <typename Iterator>
    void drawRegion(int x, int y, int w, int h, Iterator begin, Iterator end);

private:
    void initRegion(int x, int y, int w, int h);
    void writeInst(uint8_t data);
    void writeData(uint8_t data);
    
private:
    DMOLED32Display(const DMOLED32Display&) = delete;
    DMOLED32Display& operator=(const DMOLED32Display&) = delete;
};


template <typename Iterator>
inline
void DMOLED32Display::drawRegion(int x, int y, int w, int h, Iterator begin, Iterator end)
{
    initRegion(x, y, w, h);

    for (auto it(begin); it != end; ++it)
    {
        writeData(*it);
    }
}

#endif
