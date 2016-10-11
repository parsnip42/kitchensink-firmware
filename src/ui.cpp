#include "ui.h"

#include "autorepeat.h"
#include "display.h"
#include "kskeyboard.h"
#include "keyhandler.h"
#include "keymap.h"

#include <core_pins.h>
#include <string.h>

namespace
{

const unsigned char charset[] = {
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 36, 0, 8, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 70, 8, 36, 36, 8, 38, 24, 8, 16, 4, 0, 0, 0, 0, 0, 32, 60, 16, 60, 60, 64, 126, 56, 126, 60, 60, 0, 0, 0, 0, 0, 60, 62, 60, 62, 60, 30, 126, 126, 60, 66, 28, 112, 66, 2, 65, 66, 60, 62, 60, 62, 60, 127, 66, 66, 65, 66, 65, 126, 28, 2, 28, 20, 0, 0, 0, 2, 0, 64, 0, 112, 0, 2, 8, 32, 2, 12, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 48, 8, 12, 73, 8, 36, 36, 62, 41, 36, 8, 8, 8, 0, 0, 0, 0, 0, 32, 66, 24, 66, 66, 96, 2, 4, 64, 66, 66, 0, 0, 32, 0, 2, 66, 65, 66, 66, 66, 34, 2, 2, 66, 66, 8, 32, 34, 2, 99, 66, 66, 66, 66, 66, 66, 8, 66, 66, 65, 66, 65, 64, 4, 2, 16, 34, 0, 0, 0, 2, 0, 64, 0, 8, 0, 2, 8, 32, 2, 8, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 8, 8, 16, 49, 8, 0, 36, 73, 22, 36, 0, 4, 16, 0, 0, 0, 0, 0, 16, 66, 20, 66, 66, 80, 2, 2, 64, 66, 66, 0, 0, 16, 0, 4, 66, 121, 66, 66, 66, 66, 2, 2, 66, 66, 8, 32, 18, 2, 85, 66, 66, 66, 66, 66, 2, 8, 66, 66, 65, 36, 34, 64, 4, 4, 16, 0, 0, 0, 0, 2, 0, 64, 0, 8, 0, 2, 0, 0, 2, 8, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 8, 8, 16, 0, 8, 0, 126, 9, 16, 24, 0, 4, 16, 36, 8, 0, 0, 0, 16, 98, 16, 64, 64, 72, 2, 2, 32, 66, 66, 8, 8, 8, 126, 8, 66, 69, 66, 66, 2, 66, 2, 2, 2, 66, 8, 32, 10, 2, 73, 70, 66, 66, 66, 66, 2, 8, 66, 66, 65, 36, 34, 32, 4, 4, 16, 0, 0, 0, 60, 62, 60, 124, 60, 62, 124, 62, 12, 48, 66, 8, 63, 62, 60, 62, 124, 122, 124, 62, 66, 66, 65, 66, 66, 126, 8, 8, 16, 0, 8, 0, 36, 9, 8, 12, 0, 4, 16, 24, 8, 0, 0, 0, 8, 82, 16, 32, 56, 68, 62, 62, 32, 60, 66, 8, 8, 4, 0, 16, 32, 69, 66, 62, 2, 66, 30, 30, 2, 126, 8, 32, 6, 2, 73, 74, 66, 66, 66, 66, 60, 8, 66, 66, 65, 24, 20, 16, 4, 8, 16, 0, 0, 0, 64, 66, 66, 66, 66, 8, 66, 66, 8, 32, 34, 8, 73, 66, 66, 66, 66, 6, 2, 8, 66, 66, 65, 66, 66, 32, 4, 8, 32, 0, 8, 0, 36, 62, 8, 82, 0, 4, 16, 126, 62, 0, 126, 0, 8, 74, 16, 16, 64, 66, 64, 66, 16, 66, 124, 0, 0, 2, 0, 32, 16, 69, 126, 66, 2, 66, 2, 2, 114, 66, 8, 32, 6, 2, 65, 82, 66, 62, 66, 62, 64, 8, 66, 36, 73, 24, 8, 8, 4, 8, 16, 0, 0, 0, 124, 66, 2, 66, 66, 8, 66, 66, 8, 32, 18, 8, 73, 66, 66, 66, 66, 2, 2, 8, 66, 66, 73, 36, 66, 16, 8, 8, 16, 0, 8, 0, 126, 72, 4, 34, 0, 4, 16, 24, 8, 0, 0, 0, 4, 70, 16, 8, 64, 126, 64, 66, 16, 66, 64, 0, 0, 4, 126, 16, 16, 101, 66, 66, 2, 66, 2, 2, 66, 66, 8, 32, 10, 2, 65, 98, 66, 2, 66, 10, 64, 8, 66, 36, 73, 36, 8, 4, 4, 16, 16, 0, 0, 0, 66, 66, 2, 66, 126, 8, 66, 66, 8, 32, 14, 8, 73, 66, 66, 66, 66, 2, 60, 8, 66, 36, 73, 24, 66, 8, 8, 8, 16, 0, 0, 0, 36, 72, 52, 34, 0, 4, 16, 36, 8, 0, 0, 0, 4, 66, 16, 4, 66, 64, 64, 66, 8, 66, 64, 0, 0, 8, 0, 8, 0, 89, 66, 66, 66, 66, 2, 2, 66, 66, 8, 34, 18, 2, 65, 66, 66, 2, 66, 18, 66, 8, 66, 36, 85, 36, 8, 2, 4, 16, 16, 0, 0, 0, 66, 66, 2, 66, 2, 8, 66, 66, 8, 32, 18, 8, 73, 66, 66, 66, 66, 2, 64, 8, 66, 36, 73, 36, 66, 4, 8, 8, 16, 0, 8, 0, 36, 73, 74, 34, 0, 8, 8, 0, 0, 8, 0, 8, 2, 66, 16, 2, 66, 64, 66, 66, 8, 66, 32, 8, 8, 16, 0, 4, 16, 1, 66, 66, 66, 34, 2, 2, 66, 66, 8, 34, 34, 2, 65, 66, 66, 2, 82, 34, 66, 8, 66, 24, 99, 66, 8, 2, 4, 32, 16, 0, 0, 0, 66, 66, 66, 66, 2, 8, 66, 66, 8, 32, 34, 8, 73, 66, 66, 66, 66, 2, 64, 8, 66, 24, 73, 66, 66, 2, 8, 8, 16, 0, 8, 0, 36, 62, 50, 92, 0, 16, 4, 0, 0, 8, 0, 8, 2, 60, 124, 126, 60, 64, 60, 60, 8, 60, 28, 8, 8, 32, 0, 2, 16, 126, 66, 62, 60, 30, 126, 2, 60, 66, 28, 28, 66, 126, 65, 66, 60, 2, 60, 66, 60, 8, 60, 24, 65, 66, 8, 126, 28, 32, 28, 0, 0, 0, 124, 62, 60, 124, 60, 8, 124, 66, 28, 34, 66, 28, 73, 66, 60, 62, 124, 2, 62, 112, 124, 24, 62, 66, 124, 126, 48, 8, 12, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 126, 0, 0, 0, 0, 0, 0, 0, 64, 0, 0, 34, 0, 0, 0, 0, 0, 2, 64, 0, 0, 0, 0, 0, 0, 0, 64, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 60, 0, 0, 28, 0, 0, 0, 0, 0, 2, 64, 0, 0, 0, 0, 0, 0, 0, 60, 0, 0, 0, 0, 0
};

}


UI::UI(Display& display)
    : mDisplay(display)
{ }

void UI::paintText(int x, int y, const char* str)
{
    static const uint8_t color(0xf);
    static const int kCharHeight(14);
    
    int len(strlen(str));
    
    mDisplay.initRegion(x, y, len << 3, kCharHeight);
    
    for (int y(0); y < kCharHeight; ++y)
    {
        for (int x(0); x < len; ++x)
        {
            unsigned char a0(0);
            unsigned char a1(0);
            unsigned char a2(0);
            unsigned char a3(0);                

            if (str[x] > 32 && str[x] < 127)
            {
                unsigned char c(charset[str[x] - 33 + (y * 94)]);
                
                a0 = (((c>>7) & 1) * color) | ((c>>6 & 1) * (color << 4));
                a1 = (((c>>5) & 1) * color) | ((c>>4 & 1) * (color << 4));
                a2 = (((c>>3) & 1) * color) | ((c>>2 & 1) * (color << 4));
                a3 = (((c>>1) & 1) * color) | ((c & 1)    * (color << 4));
            }

            mDisplay.writeData(a3);
            mDisplay.writeData(a2);
            mDisplay.writeData(a1);
            mDisplay.writeData(a0);
        }
    }
}

void UI::paintText(int x, int y, const char* str, bool inv, uint8_t fg, uint8_t bg)
{
    static const int kCharHeight(14);
    
    int len(strlen(str));
    
    mDisplay.initRegion(x, y, len << 3, kCharHeight);

    if (inv)
    {
        uint8_t t(fg);
        fg = bg;
        bg = t;
    }

    uint8_t colorMap[] = {
        uint8_t(bg | (bg << 4)),
        uint8_t(bg | (fg << 4)),
        uint8_t(fg | (bg << 4)),
        uint8_t(fg | (fg << 4)),
    };
    
    for (int y(0); y < kCharHeight; ++y)
    {
        for (int x(0); x < len; ++x)
        {
            if (str[x] > 32 && str[x] < 127)
            {
                uint8_t c(charset[str[x] - 33 + (y * 94)]);

                mDisplay.writeData(colorMap[c & 0x3]);
                mDisplay.writeData(colorMap[(c >> 2) & 0x3]);
                mDisplay.writeData(colorMap[(c >> 4) & 0x3]);
                mDisplay.writeData(colorMap[(c >> 6) & 0x3]);

            }
            else if (str[x] == 32)
            {
                mDisplay.writeData(bg | (bg << 4));
                mDisplay.writeData(bg | (bg << 4));
                mDisplay.writeData(bg | (bg << 4));
                mDisplay.writeData(bg | (bg << 4));
            }
        }
    }
}

void UI::menu(KeyHandler& keyHandler,
              EventQueue& eventQueue)
{
    mDisplay.clear();

    bool quit(false);
    int selected(0);
    
    for (int color = 0; color <= 0xf; ++color)
    {
        paintText(28, 0,  "             Macros             ", selected == 0, color);
        paintText(28, 14, "             Display            ", selected == 1, color);
        paintText(28, 28, "          Configuration         ", selected == 2, color);
        paintText(28, 42, "             System             ", selected == 3, color);
        delay(4);
    }

    int counter(0);
    mDisplay.scroll(counter);

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
                eventQueue.pushBack(KeyEvent(KeyId::Action(9), KeyState::kPressed, 2));
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
                    mDisplay.scroll(counter);
                    delay(10);
                }
                
                paintText(28, 0,  "             Macros             ", selected == 0);
                paintText(28, 14, "             Display            ", selected == 1);
                paintText(28, 28, "          Configuration         ", selected == 2);
                paintText(28, 42, "             System             ", selected == 3);
            }
            
            if (event.keyId.value() == 81 && event.state == KeyState::kPressed)
            {
                selected = (selected + 1) % 4;

                paintText(28, 0,  "             Macros             ", selected == 0);
                paintText(28, 14, "             Display            ", selected == 1);
                paintText(28, 28, "          Configuration         ", selected == 2);
                paintText(28, 42, "             System             ", selected == 3);

                for (int i = 0; i < 14; i++)
                {
                    counter++;
                    mDisplay.scroll(counter);
                    delay(10);
                }
                
            }
        }
    }

    for (int color = 0xf; color >= 0; --color)
    {
        paintText(28, 0,  "             Macros             ", selected == 0, color);
        paintText(28, 14, "             Display            ", selected == 1, color);
        paintText(28, 28, "          Configuration         ", selected == 2, color);
        paintText(28, 42, "             System             ", selected == 3, color);
        delay(4);
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
    
    mDisplay.clear();
}

void UI::clear()
{
    mDisplay.clear();
}
