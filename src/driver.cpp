#include "Wire.h"
#include "SdFat.h"

#include "usb_keyboard.h"

#include "display.h"
#include "keymatrix.h"
#include "keymap.h"


SdFat sd;

void setup() {

    Wire.begin();
    Wire.setClock(400000);
}


void loop() {
    Display display;

    display.init();
    display.paint(30, 0, "Start");
    
    KeyMatrix matrixA(0x20, 0x7C00, 0x3FF);
    KeyMatrix matrixB(0x21, 0x3E00, 0xC0FF);
    
    display.paint(30, 14, "Config");


    if (!sd.begin(10, SPI_HALF_SPEED)) {
        if (sd.card()->errorCode()) {
            char sderr[48];
            sprintf(sderr,"SD Failed : 0x%x", sd.card()->errorCode());
            display.paint(30, 28, sderr);
        }
    }
    else
    {
        char sdinfo[48];
        sprintf(sdinfo, "SD OK : %dMB / FAT%d", (int)(0.000512 * sd.card()->cardSize() + 0.5), sd.vol()->fatType());
        display.paint(30, 28, sdinfo);

        SdBaseFile myFile;

        if (!myFile.open("test.cfg", O_READ)) {
            display.paint(30, 42, "Couldn't open file");
        }
        else
        {
            char data[48];

            myFile.fgets(data, sizeof(data));
            
            display.paint(30, 42, data);

            myFile.close();
        }
    }

    
    char outStr[48];

    bool displayDebug = true;
    
    while (1)
    {
        auto callback([](const KeyMatrix::Event& event)
                      {
                          
                      });
        
        matrixA.scan(callback);
        matrixB.scan(callback);

        if (displayDebug)
        {
            sprintf(outStr,"|%4.4x%4.4x%4.4x%4.4x%4.4x|",
                    (int)matrixA[0].data(),
                    (int)matrixA[1].data(),
                    (int)matrixA[2].data(),
                    (int)matrixA[3].data(),
                    (int)matrixA[4].data());
            display.paint(48, 0, outStr);

            sprintf(outStr,"|%4.4x%4.4x%4.4x%4.4x%4.4x|",
                    (int)matrixB[0].data(),
                    (int)matrixB[1].data(),
                    (int)matrixB[2].data(),
                    (int)matrixB[3].data(),
                    (int)matrixB[4].data());
            display.paint(48, 14, outStr);
        }
        
        keyboard_modifier_keys = 0;
        keyboard_keys[0] = 0;
        keyboard_keys[1] = 0;
        keyboard_keys[2] = 0;
        keyboard_keys[3] = 0;
        keyboard_keys[4] = 0;
        keyboard_keys[5] = 0;

        int32_t key = 0;

        KeyMap kmapAL0({
                {0,MODIFIERKEY_LEFT_GUI,0,0,0,MODIFIERKEY_LEFT_SHIFT<<16|KEY_UP,MODIFIERKEY_LEFT_CTRL,0,0,MODIFIERKEY_LEFT_ALT,0,0,0,0,0,0},
                {0,MODIFIERKEY_LEFT_SHIFT,KEY_Z,KEY_X,KEY_C,KEY_V,KEY_B,0,0,0,0,0,0,0,KEY_F8,KEY_F7},
                {0,0,KEY_A,KEY_S,KEY_D,KEY_F,KEY_G,0,0,0,0,0,0,0,KEY_F6,KEY_F5},
                {0,MODIFIERKEY_LEFT_SHIFT<<16|KEY_MINUS,KEY_Q,KEY_W,KEY_E,KEY_R,KEY_T,KEY_TAB,0,0,0,0,0,0,KEY_F4,KEY_F3},
                {KEY_TILDE,KEY_NON_US_BS,KEY_1,KEY_2,KEY_3,KEY_4,KEY_5,KEY_NON_US_NUM,0,KEY_ESC,0,0,0,0,KEY_F2,KEY_F1},
            });
        
        KeyMap kmapBL0({
                {KEY_QUOTE,KEY_6,KEY_7,KEY_8,KEY_9,KEY_0,KEY_MINUS,KEY_EQUAL,0,0,0,0,0,0,KEY_F2,KEY_F1 },
                {KEY_BACKSPACE,KEY_Y,KEY_U,KEY_I,KEY_O,KEY_P,KEY_LEFT_BRACE,KEY_RIGHT_BRACE,0,0,0,0,0,0,KEY_F4,KEY_F3 },
                {0,KEY_H,KEY_J,KEY_K,KEY_L,KEY_SEMICOLON,KEY_ENTER,0,0,0,0,0,0,0,KEY_F6,KEY_F5 },
                {KEY_DELETE,KEY_N,KEY_M,KEY_COMMA,KEY_PERIOD,KEY_SLASH,MODIFIERKEY_RIGHT_SHIFT,0,0,0,0,0,0,0,KEY_F8,KEY_F7 },
                {KEY_SPACE,MODIFIERKEY_RIGHT_CTRL,KEY_END,KEY_LEFT,KEY_UP,KEY_DOWN,KEY_RIGHT,0,0,0,0,0,0,0,MODIFIERKEY_LEFT_ALT,0 }
            });
        
        KeyMap kmapBL1({
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                { KEY_BACKSPACE, KEY_PAGE_UP, KEY_END, KEY_UP, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                { 0, KEY_HOME, KEY_LEFT,KEY_DOWN,KEY_RIGHT,0,0,0,0,0,0,0,0,0,0,0  },
                { 0, KEY_PAGE_DOWN, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                { 0, MODIFIERKEY_RIGHT_CTRL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, MODIFIERKEY_LEFT_ALT, 0 }
            });
        
        KeyMap kmapAL2({
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                { 0, 0, KEY_F11, KEY_F12, KEY_F13, KEY_F14, KEY_F15, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                { 0, 0, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                { 0, 0, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
            });

        KeyMap kmapBL2({
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                { 0, 0, KEY_7, KEY_8, KEY_9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                { 0, 0, KEY_4, KEY_5, KEY_6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                { 0, 0, KEY_1, KEY_2, KEY_3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                { 0, 0, KEY_0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
            });

        KeyMap *kmapA = &kmapAL0;
        KeyMap *kmapB = &kmapBL0;
        
        if (matrixA[0][7])
        {
            kmapB=&kmapBL1;

            if (displayDebug)
            {
                display.paint(60, 42, "L1");
            }
        }
        else if (matrixA[2][1])
        {
            kmapA=&kmapAL2;
            kmapB=&kmapBL2;

            if (displayDebug)
            {
                display.paint(60, 42, "L2");
            }
        }
        else
        {
            if (displayDebug)
            {
                display.paint(60, 42, "L0");
            }
        }

        if (matrixA[1][8] && matrixA.delta()[1][8])
        {
            displayDebug = !displayDebug;
            
            if (!displayDebug)
            {
                display.clear();
            }
        }
        
        keyboard_modifier_keys = 0;

        
        for (int row = 0; row < 5; ++row)
        {
            for (int i = 0; i < 16; ++i)
            {
                int keyCodeA((*kmapA)[row][i]);
                
                if (matrixA[row][i] && keyCodeA)
                {
                    if (keyCodeA & 0x80000000)
                    {
                        keyboard_modifier_keys |= ((keyCodeA >> 16) & 0xff);
                    }

                    if (keyCodeA & 0x8000)
                    {
                        keyboard_modifier_keys |= (keyCodeA & 0xff);
                    }
                    else if (keyCodeA & 0xff)
                    {
                        keyboard_keys[key++] = keyCodeA & 0xff;
                    }
                }

                int keyCodeB((*kmapB)[row][i]);

                if (matrixB[row][i] && keyCodeB)
                {
                    if (keyCodeB & 0x80000000)
                    {
                        keyboard_modifier_keys |= ((keyCodeB >> 16) & 0xff);
                    }
                    
                    if (keyCodeB & 0x8000)
                    {
                        keyboard_modifier_keys |= (keyCodeB & 0xff);
                    }
                    else if (keyCodeB & 0xff)
                    {
                        keyboard_keys[key++] = keyCodeB & 0xff;
                    }
                }
            }
        }

        usb_keyboard_send(); 
    }
    
    delay(5000000);
}
