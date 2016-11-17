#ifndef INCLUDED_UI_MENU_H
#define INCLUDED_UI_MENU_H

#include "eventqueue.h"
#include "keyhandler.h"
#include "keyid.h"

#include "ui/surface.h"

#include <elapsedMillis.h>

namespace UI
{

class Surface;

class Menu
{
public:
    class Item
    {
    public:
        constexpr Item(const char*  nText,
                       const KeyId& nKeyId)
            : text(nText)
            , keyId(nKeyId)
        { }

    public:
        const char* text;
        KeyId       keyId;
    };
    
public:
    explicit Menu(Surface& surface);

public:
    template <typename Iterator>
    void createMenu(KeyHandler& keyHandler,
                    EventQueue& eventQueue,
                    Iterator    begin,
                    Iterator    end,
                    Iterator    selected);

    
    template <typename Iterator>
    void paintMenu(uint8_t  fg,
                   uint8_t  bg,
                   Iterator begin,
                   Iterator end,
                   Iterator selected);
    
    void paint();
    
private:
    Surface& mSurface;

private:
    Menu(const Menu&) = delete;
    Menu& operator=(const Menu&) = delete;
};

template <typename Iterator>
inline
void Menu::createMenu(KeyHandler& keyHandler,
                      EventQueue& eventQueue,
                      Iterator    begin,
                      Iterator    end,
                      Iterator    selected)
{
    for (uint8_t c(0); c < 0xf; ++c)
    {
        auto now(millis());
        paintMenu(c, 0, begin, end, selected);
        while ((millis() - now) < 50);
    }
    
    while (1)
    {
        keyHandler.poll(eventQueue);
        
        if (!eventQueue.empty())
        {
            auto event(eventQueue.pop());

            if (event.pressed)
            {
                const auto& keyId(event.keyId);
                
                if (keyId == KeyId(81))
                {
                    ++selected;
                    
                    if (selected == end)
                    {
                        selected = begin;
                    }
                }
                
                if (keyId == KeyId(82))
                {
                    if (selected == begin)
                    {
                        selected = end;
                    }
                    
                    --selected;
                }

                if (keyId == KeyId(40))
                {
                    
                    break;
                }
            }
        }

        paintMenu(0xf, 0, begin, end, selected);
    }

    for (int c(0xf); c >= 0; --c)
    {
        auto now(millis());
        paintMenu(c, 0, begin, end, selected);
        while ((millis() - now) < 50);
    }
}


template <typename Iterator>
inline
void Menu::paintMenu(uint8_t  fg,
                     uint8_t  bg,
                     Iterator begin,
                     Iterator end,
                     Iterator selected)
{
    int len(3);
    
    const uint8_t colorMap[] =
    {
        uint8_t(bg | (bg << 4)),
        uint8_t(bg | (fg << 4)),
        uint8_t(fg | (bg << 4)),
        uint8_t(fg | (fg << 4)),
    };
    
    const uint8_t invColorMap[] =
    {
        uint8_t(fg | (fg << 4)),
        uint8_t(fg | (bg << 4)),
        uint8_t(bg | (fg << 4)),
        uint8_t(bg | (bg << 4)),
    };

    auto current(begin);
    auto line(0);
    
    mSurface.initRegion(28, 0, len << 3, 64);
    
    for (int y(0); y < 64; ++y)
    {
        if (line > 13)
        {
            line = 0;
            ++current;

            if (current == end)
            {
                current = begin;
            }
        }

        const auto& colors(current != selected ? colorMap : invColorMap);
        auto text(current->text);

        
        mSurface.paintTextLine(text, text+len, line, colors);

        ++line;
    }
}

}

#endif
