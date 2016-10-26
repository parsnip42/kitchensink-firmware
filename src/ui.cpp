#include "ui.h"
/*
#include "autorepeat.h"
#include "display.h"
#include "kskeyboard.h"
#include "keyhandler.h"
#include "keymap.h"
#include "layerstack.h"

#include <core_pins.h>
#include <string.h>
#include <cmath>

namespace
{

const unsigned char charset[] = {
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 36, 0, 8, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 70, 8, 36, 36, 8, 38, 24, 8, 16, 4, 0, 0, 0, 0, 0, 32, 60, 16, 60, 60, 64, 126, 56, 126, 60, 60, 0, 0, 0, 0, 0, 60, 62, 60, 62, 60, 30, 126, 126, 60, 66, 28, 112, 66, 2, 65, 66, 60, 62, 60, 62, 60, 127, 66, 66, 65, 66, 65, 126, 28, 2, 28, 20, 0, 0, 0, 2, 0, 64, 0, 112, 0, 2, 8, 32, 2, 12, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 48, 8, 12, 73, 8, 36, 36, 62, 41, 36, 8, 8, 8, 0, 0, 0, 0, 0, 32, 66, 24, 66, 66, 96, 2, 4, 64, 66, 66, 0, 0, 32, 0, 2, 66, 65, 66, 66, 66, 34, 2, 2, 66, 66, 8, 32, 34, 2, 99, 66, 66, 66, 66, 66, 66, 8, 66, 66, 65, 66, 65, 64, 4, 2, 16, 34, 0, 0, 0, 2, 0, 64, 0, 8, 0, 2, 8, 32, 2, 8, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 8, 8, 16, 49, 8, 0, 36, 73, 22, 36, 0, 4, 16, 0, 0, 0, 0, 0, 16, 66, 20, 66, 66, 80, 2, 2, 64, 66, 66, 0, 0, 16, 0, 4, 66, 121, 66, 66, 66, 66, 2, 2, 66, 66, 8, 32, 18, 2, 85, 66, 66, 66, 66, 66, 2, 8, 66, 66, 65, 36, 34, 64, 4, 4, 16, 0, 0, 0, 0, 2, 0, 64, 0, 8, 0, 2, 0, 0, 2, 8, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 8, 8, 16, 0, 8, 0, 126, 9, 16, 24, 0, 4, 16, 36, 8, 0, 0, 0, 16, 98, 16, 64, 64, 72, 2, 2, 32, 66, 66, 8, 8, 8, 126, 8, 66, 69, 66, 66, 2, 66, 2, 2, 2, 66, 8, 32, 10, 2, 73, 70, 66, 66, 66, 66, 2, 8, 66, 66, 65, 36, 34, 32, 4, 4, 16, 0, 0, 0, 60, 62, 60, 124, 60, 62, 124, 62, 12, 48, 66, 8, 63, 62, 60, 62, 124, 122, 124, 62, 66, 66, 65, 66, 66, 126, 8, 8, 16, 0, 8, 0, 36, 9, 8, 12, 0, 4, 16, 24, 8, 0, 0, 0, 8, 82, 16, 32, 56, 68, 62, 62, 32, 60, 66, 8, 8, 4, 0, 16, 32, 69, 66, 62, 2, 66, 30, 30, 2, 126, 8, 32, 6, 2, 73, 74, 66, 66, 66, 66, 60, 8, 66, 66, 65, 24, 20, 16, 4, 8, 16, 0, 0, 0, 64, 66, 66, 66, 66, 8, 66, 66, 8, 32, 34, 8, 73, 66, 66, 66, 66, 6, 2, 8, 66, 66, 65, 66, 66, 32, 4, 8, 32, 0, 8, 0, 36, 62, 8, 82, 0, 4, 16, 126, 62, 0, 126, 0, 8, 74, 16, 16, 64, 66, 64, 66, 16, 66, 124, 0, 0, 2, 0, 32, 16, 69, 126, 66, 2, 66, 2, 2, 114, 66, 8, 32, 6, 2, 65, 82, 66, 62, 66, 62, 64, 8, 66, 36, 73, 24, 8, 8, 4, 8, 16, 0, 0, 0, 124, 66, 2, 66, 66, 8, 66, 66, 8, 32, 18, 8, 73, 66, 66, 66, 66, 2, 2, 8, 66, 66, 73, 36, 66, 16, 8, 8, 16, 0, 8, 0, 126, 72, 4, 34, 0, 4, 16, 24, 8, 0, 0, 0, 4, 70, 16, 8, 64, 126, 64, 66, 16, 66, 64, 0, 0, 4, 126, 16, 16, 101, 66, 66, 2, 66, 2, 2, 66, 66, 8, 32, 10, 2, 65, 98, 66, 2, 66, 10, 64, 8, 66, 36, 73, 36, 8, 4, 4, 16, 16, 0, 0, 0, 66, 66, 2, 66, 126, 8, 66, 66, 8, 32, 14, 8, 73, 66, 66, 66, 66, 2, 60, 8, 66, 36, 73, 24, 66, 8, 8, 8, 16, 0, 0, 0, 36, 72, 52, 34, 0, 4, 16, 36, 8, 0, 0, 0, 4, 66, 16, 4, 66, 64, 64, 66, 8, 66, 64, 0, 0, 8, 0, 8, 0, 89, 66, 66, 66, 66, 2, 2, 66, 66, 8, 34, 18, 2, 65, 66, 66, 2, 66, 18, 66, 8, 66, 36, 85, 36, 8, 2, 4, 16, 16, 0, 0, 0, 66, 66, 2, 66, 2, 8, 66, 66, 8, 32, 18, 8, 73, 66, 66, 66, 66, 2, 64, 8, 66, 36, 73, 36, 66, 4, 8, 8, 16, 0, 8, 0, 36, 73, 74, 34, 0, 8, 8, 0, 0, 8, 0, 8, 2, 66, 16, 2, 66, 64, 66, 66, 8, 66, 32, 8, 8, 16, 0, 4, 16, 1, 66, 66, 66, 34, 2, 2, 66, 66, 8, 34, 34, 2, 65, 66, 66, 2, 82, 34, 66, 8, 66, 24, 99, 66, 8, 2, 4, 32, 16, 0, 0, 0, 66, 66, 66, 66, 2, 8, 66, 66, 8, 32, 34, 8, 73, 66, 66, 66, 66, 2, 64, 8, 66, 24, 73, 66, 66, 2, 8, 8, 16, 0, 8, 0, 36, 62, 50, 92, 0, 16, 4, 0, 0, 8, 0, 8, 2, 60, 124, 126, 60, 64, 60, 60, 8, 60, 28, 8, 8, 32, 0, 2, 16, 126, 66, 62, 60, 30, 126, 2, 60, 66, 28, 28, 66, 126, 65, 66, 60, 2, 60, 66, 60, 8, 60, 24, 65, 66, 8, 126, 28, 32, 28, 0, 0, 0, 124, 62, 60, 124, 60, 8, 124, 66, 28, 34, 66, 28, 73, 66, 60, 62, 124, 2, 62, 112, 124, 24, 62, 66, 124, 126, 48, 8, 12, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 126, 0, 0, 0, 0, 0, 0, 0, 64, 0, 0, 34, 0, 0, 0, 0, 0, 2, 64, 0, 0, 0, 0, 0, 0, 0, 64, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 60, 0, 0, 28, 0, 0, 0, 0, 0, 2, 64, 0, 0, 0, 0, 0, 0, 0, 60, 0, 0, 0, 0, 0
};

}


UI::UI(Display& display)
    : mDisplay(display)
{ }

void UI::paintText(int         x,
                   int         y,
                   const char* str,
                   uint8_t     fg,
                   uint8_t     bg)
{
    static const int kCharHeight(14);
    
    auto len(strlen(str));
    
    mDisplay.initRegion(x, y, len << 3, kCharHeight);

    const uint8_t colorMap[] =
    {
        uint8_t(bg | (bg << 4)),
        uint8_t(bg | (fg << 4)),
        uint8_t(fg | (bg << 4)),
        uint8_t(fg | (fg << 4)),
    };
    
    
    for (int line(0); line < kCharHeight; ++line)
    {
        paintTextLine(str, str + len, line, colorMap);
    }
}

void UI::paintTextLine(const char*   begin,
                       const char*   end,
                       const int     line,
                       const uint8_t (&colorMap)[4])
{
    for (auto it(begin); it != end; ++it)
    {
        const auto chr(*it);
        
        if (chr > 32 && chr < 127)
        {
            uint8_t data(charset[chr - 33 + (line * 94)]);
            
            mDisplay.writeData(colorMap[data & 0x3]);
            mDisplay.writeData(colorMap[(data >> 2) & 0x3]);
            mDisplay.writeData(colorMap[(data >> 4) & 0x3]);
            mDisplay.writeData(colorMap[(data >> 6) & 0x3]);

        }
        else if (chr == 32)
        {
            mDisplay.writeData(colorMap[0]);
            mDisplay.writeData(colorMap[0]);
            mDisplay.writeData(colorMap[0]);
            mDisplay.writeData(colorMap[0]);
        }
    }   
}

void UI::paintMenu(UIMenu::Data& dataSource, int point, uint8_t fgBase, int selected)
{
    uint8_t bg(0);

    int len(30);

    mDisplay.initRegion(28, 0, len << 3, 64);

    const uint8_t invColorMap[] =
    {
        uint8_t(fgBase | (fgBase << 4)),
        uint8_t(fgBase | (bg << 4)),
        uint8_t(bg | (fgBase << 4)),
        uint8_t(bg | (bg << 4)),
    };

    for (auto offset(point); offset < point + 64; ++offset)
    {
        int f(32-std::abs(32-(offset-point)));
        uint8_t fg(f < fgBase ? f : fgBase);

        const uint8_t colorMap[] =
        {
            uint8_t(bg | (bg << 4)),
            uint8_t(bg | (fg << 4)),
            uint8_t(fg | (bg << 4)),
            uint8_t(fg | (fg << 4)),
        };

        auto index((point + offset) / 14);
        auto line((point + offset) % 14);

        const char* text(dataSource.entry(index % dataSource.size()).text);

        if ((index % dataSource.size()) == (selected % dataSource.size()))
        {
            paintTextLine(text, text+len, line, invColorMap);
        }
        else
        {
            paintTextLine(text, text+len, line, colorMap);
        }
    }
}

int UI::scrollMenu(UIMenu::Data& dataSource, int point, int direction)
{
    uint8_t fg(0xf);
    uint8_t bg(0);

    const uint8_t colorMap[] =
    {
        uint8_t(bg | (bg << 4)),
        uint8_t(bg | (fg << 4)),
        uint8_t(fg | (bg << 4)),
        uint8_t(fg | (fg << 4)),
    };

    int len(30);

    mDisplay.scroll((point + direction) % 64);

    auto yStart(point + 64);

    if (direction > 0)
    {
        mDisplay.initRegion(28, yStart % 64, len << 3, direction);
    
        for (auto offset(yStart); offset < yStart + direction; ++offset)
        {
            auto index(offset / 14);
            auto line(offset % 14);

            const char* text(dataSource.entry(index % dataSource.size()).text);
            paintTextLine(text, text+len, line, colorMap);
        }
    }
    else
    {
        mDisplay.initRegion(28, (yStart - direction) % 64, len << 3, direction);
    
        for (auto offset(yStart - direction); offset < yStart; ++offset)
        {
            auto index(offset / 14);
            auto line(offset % 14);

            const char* text(dataSource.entry(index % dataSource.size()).text);
            paintTextLine(text, text+len, line, colorMap);
        }
    }

    return direction;
}

void UI::main(const LayerStack& layerStack)
{
    for (int i = 1; i < 10; ++i)
    {
        const char* text(layerStack.enabled(i) ? layerStack[i].name() : "          ");

        paintText(28+((i&1) * 20), (i >> 1) * 14, text, 0xf, 0);
    }
}

void UI::menu(UIMenu::Data& dataSource,
              KeyHandler& keyHandler,
              EventQueue& eventQueue)
{
    mDisplay.clear();

    int selected(2);
    
    for (uint8_t i(0); i <= 0xf; ++i)
    {
        paintMenu(dataSource, 0, i, selected);
        delay(12);
    }
    AutoRepeat autoRepeat(500);
    int offset(3);
    bool quit(false);
    while (!quit)
    {    
        keyHandler.poll(eventQueue);
        
        while (!eventQueue.empty())
        {
            auto event(eventQueue.pop());
            autoRepeat.processKey(event.keyId, event.state);

            if (event.keyId.value() == 41 && event.state == KeyState::kPressed)
            {
                quit = true;
            }
        }

        auto activeKey(autoRepeat.activeKey());
        
        if (activeKey.value() == 82)
        {
            --selected;
            for (int i(0); i < 7; ++i)
            {
                keyHandler.poll(eventQueue);
                paintMenu(dataSource, --offset, 0xf, selected);
                delay(8);
            }
        }

        if (activeKey.value() == 81)
        {
            ++selected;
            for (int i(0); i < 7; ++i)
            {
                keyHandler.poll(eventQueue);
                paintMenu(dataSource, ++offset, 0xf, selected);
                delay(8);
            }
        }
    }

    // for (uint8_t i(0xf); i >=0; --i)
    // {
    //     paintMenu(dataSource, offset, i);
    //     delay(12);
    // }
    
    mDisplay.clear();

    // int offset(0);
    // offset += scrollMenu(dataSource, offset, 64);
    
    // for (int i(0); i < 200; ++i)
    // {
    //     offset += scrollMenu(dataSource, offset, 1);
    //     delay(12);
    // }




    bool quit(false);
    std::size_t selected(0);
    
    for (int color = 0; color <= 0xf; ++color)
    {
        for (std::size_t i(0); i < dataSource.size(); ++i)
        {
            if (selected != i)
            {
                paintText(28, i*14, dataSource.entry(i).text, color, 0x0);
            }
            else
            {
                paintText(28, i*14, dataSource.entry(i).text, 0x0, color);
            }

            delay(4);
        }
    }

    int counter(0);

    while (!quit)
    {    
        keyHandler.poll(eventQueue);
        
        while (!eventQueue.empty())
        {
            auto event(eventQueue.pop());

            if (event.keyId.type() == KeyId::kModifier)
            {
                if (event.keyId.value() >= 10)
                {
                    int layerId(event.keyId.value() - 10);
                    bool state(event.state == KeyState::kPressed);

                    keyHandler.setLayer(layerId, state, eventQueue);
                }
            }

            if (event.keyId.value() == 40 && event.state == KeyState::kPressed)
            {
                eventQueue.pushBack(dataSource.entry(selected).keyEvent);
                quit = true;
                break;
            }

            if (event.keyId.value() == 41 && event.state == KeyState::kPressed)
            {
                quit = true;
            }
            
            if (event.keyId.value() == 82 && event.state == KeyState::kPressed)
            {
                selected = (selected + 3) % 4;
                
                for (int i = 0; i < 14; i++)
                {
                    counter--;
                    // mDisplay.scroll(counter);
                    delay(10);
                }

                for (std::size_t i(0); i < dataSource.size(); ++i)
                {
                    if (selected != i)
                    {
                        paintText(28, i*14, dataSource.entry(i).text);
                    }
                    else
                    {
                        paintText(28, i*14, dataSource.entry(i).text, 0x0, 0xf);
                    }
                }
            }
            
            if (event.keyId.value() == 81 && event.state == KeyState::kPressed)
            {
                selected = (selected + 1) % 4;

                for (std::size_t i(0); i < dataSource.size(); ++i)
                {
                    if (selected != i)
                    {
                        paintText(28, i*14, dataSource.entry(i).text);
                    }
                    else
                    {
                        paintText(28, i*14, dataSource.entry(i).text, 0x0, 0xf);
                    }
                }

                for (int i = 0; i < 14; i++)
                {
                    counter++;
                    // mDisplay.scroll(counter);
                    delay(10);
                }
                
            }
        }
    }

    for (int color = 0xf; color >= 0; --color)
    {
        for (std::size_t i(0); i < dataSource.size(); ++i)
        {
            if (selected != i)
            {
                paintText(28, i*14, dataSource.entry(i).text, color, 0x0);
            }
            else
            {
                paintText(28, i*14, dataSource.entry(i).text, 0x0, color);
            }

            delay(4);
        }
    }

    // AutoRepeat autoRepeat(660);
    // char str[32]={0};
    // size_t len(0);
    
    // while (!quit)
    // {
        // keyHandler.poll([&](const KeyEvent& event)
        // {
        //     if (event.keyId.type() == KeyId::kKey)
        //     {
        //         if (event.keyId.value() == 0x28)
        //         {
        //             quit = true;
        //         }
        //         else
        //         {
        //             autoRepeat.processKey(event.keyId,
        //                                   event.state);
                
        //             KeyId current(autoRepeat.activeKey());

        //             if (current != KeyId::None)
        //             {
        //                 if (event.keyId.value() == 0x2a)
        //                 {
        //                     if (len > 0)
        //                     {
        //                         str[--len] = ' ';
        //                     }
        //                 }
        //                 else
        //                 {
        //                     str[len++] = KeyMap::table()[event.keyId.value()].dflt[0];
        //                 }
        //             }
        //         }
        //     }
        // });

        // paintText(28, 0, str);
    // }
    
    // mDisplay.clear();
}

void UI::clear()
{
    mDisplay.clear();
}

*/
