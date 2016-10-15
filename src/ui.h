#ifndef INCLUDED_UI_H
#define INCLUDED_UI_H

#include "eventqueue.h"
#include "keyevent.h"

class Display;
class KeyHandler;

class UIMenu
{
public:
    class Entry
    {
    public:
        Entry()
        { }
        
        explicit Entry(const char*     nText,
                       const KeyEvent& nKeyEvent,
                       bool            nExit = false)
            : text(nText)
            , keyEvent(nKeyEvent)
            , exit(nExit)
        { }
        
    public:
        const char* text;
        KeyEvent    keyEvent;
        bool        exit;
    };
    
public:
    class Data
    {
    public:
        Data() { };
        virtual ~Data() { };
        
    public:
        virtual Entry entry(std::size_t n) = 0;
        virtual std::size_t size() = 0;
    };

};

class UI
{
public:
    explicit UI(Display& display);

public:
    void menu(UIMenu::Data& dataSource,KeyHandler& keyHandler, EventQueue& eventQueue);
    void paintText(int         x,
                   int         y,
                   const char* str,
                   uint8_t     fg = 0xf,
                   uint8_t     bg = 0);
    void clear();

private:
    void paintTextLine(const char*   begin,
                       const char*   end,
                       const int     line,
                       const uint8_t (&colorMap)[4]);


private:
    Display& mDisplay;
    
private:
    UI(const UI&) = delete;
    UI& operator=(const UI&) = delete;
};

#endif
