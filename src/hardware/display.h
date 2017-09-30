#ifndef INCLUDED_DISPLAY_H
#define INCLUDED_DISPLAY_H

#include <cstdint>

class Display
{
public:
    Display();

public:
    void init();
    void clear();

    void initRegion(int x, int y, int w, int h);

    
    template <typename Iterator>
    void drawRegion(int x, int y, int w, int h, Iterator begin, Iterator end);

public:
    void writeInst(uint8_t data);
    void writeData(uint8_t data);
    
private:
    Display(const Display&) = delete;
    Display& operator=(const Display&) = delete;
};


template <typename Iterator>
inline
void Display::drawRegion(int x, int y, int w, int h, Iterator begin, Iterator end)
{
    initRegion(x, y, w, h);

    for (auto it(begin); it != end; ++it)
    {
        writeData(*it);
    }
}

#endif
