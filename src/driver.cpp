
#include "actioncontext.h"
#include "actionmanager.h"
#include "actions.h"
#include "ctrlutil.h"
#include "display.h"
#include "keyhandler.h"
#include "kskeyboard.h"
#include "layer.h"
#include "ui.h"
#include "usbkeyboard.h"

#include "SdFat.h"

const Layer layer0(
    {
        { KEY_TILDE,KEY_NON_US_BS,KEY_1,KEY_2,KEY_3,KEY_4,KEY_5,KEY_NON_US_NUM,KeyId::Layer(2),0,
            KEY_F1,KEY_F2,KEY_QUOTE,KEY_6,KEY_7,KEY_8,KEY_9,KEY_0,KEY_MINUS,KEY_EQUAL },
        
        { KEY_ESC,KeyId::Action(4),KEY_Q,KEY_W,KEY_E,KEY_R,KEY_T,KEY_TAB,0,0,
            KEY_F3,KEY_F4,KEY_BACKSPACE,KEY_Y,KEY_U,KEY_I,KEY_O,KEY_P,KEY_LEFT_BRACE,KEY_RIGHT_BRACE },
        
        {0,KeyId::Layer(2),KEY_A,KEY_S,KEY_D,KEY_F,KEY_G,0,0,0,
            KEY_F6,KEY_F5, 0,KEY_H,KEY_J,KEY_K,KEY_L,KEY_SEMICOLON,KEY_ENTER },
        
        {0,ModifierId::kLShift,KEY_Z,KEY_X,KEY_C,KEY_V,KEY_B,0,KeyId::Action(5),KeyId::Action(2),
            KeyId::Action(9),0,KEY_DELETE,KEY_N,KEY_M,KEY_COMMA,KEY_PERIOD,KEY_SLASH,ModifierId::kRShift },
        
        {0,ModifierId::kLGui,0,0,0,0,ModifierId::kLCtrl,KeyId::Layer(1),ModifierId::kLAlt,0,
            0,ModifierId::kLAlt,KEY_SPACE,ModifierId::kRCtrl,KEY_END,KEY_LEFT,KEY_UP,KEY_DOWN,KEY_RIGHT }
    });

const Layer layer1(
    {
        { },
        
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, KEY_BACKSPACE, KEY_PAGE_UP, KEY_END, KEY_UP, 0, 0, 0 },
        
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, KEY_HOME, KEY_LEFT,KEY_DOWN,KEY_RIGHT, 0, 0, 0 },
        
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, KEY_PAGE_DOWN, 0, 0, 0, 0, 0, 0 }
    });

const Layer layer2(
    {
        { },
        
        { 0, 0, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, 0, 0, 0,
            0, 0, 0, 0, KEY_7, KEY_8, KEY_9, 0, 0, 0 },
        
        { 0, 0, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, 0, 0, 0,
            0, 0, 0, 0, KEY_4, KEY_5, KEY_6, 0, 0, 0 },
        
        { 0, 0, KEY_F11, KEY_F12, KEY_F13, KEY_F14, KEY_F15, 0, 0, 0,
            0, 0, 0, 0, KEY_1, KEY_2, KEY_3, 0, 0, 0 },
        
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, KEY_0, 0, 0, 0, 0, 0 }
    });


const Layer layer3(
    {
        { KEY_TILDE,KEY_NON_US_BS,KEY_1,KEY_2,KEY_3,KEY_4,KEY_5,KEY_NON_US_NUM,KeyId::Action(3),0,
            KEY_F1,KEY_F2,KEY_QUOTE,KEY_6,KEY_7,KEY_8,KEY_9,KEY_0,KEY_MINUS,KEY_EQUAL },
        
        { KEY_ESC,KeyId::Action(4),KEY_Q,KEY_W,KEY_E,KEY_R,KEY_T,KEY_TAB,0,0,
            KEY_F3,KEY_F4,KEY_BACKSPACE,KEY_Y,KEY_U,KEY_I,KEY_O,KEY_P,KEY_LEFT_BRACE,KEY_RIGHT_BRACE },
        
        {0,KEY_TAB,KEY_A,KEY_S,KEY_D,KEY_F,KEY_G,0,0,0,
            KEY_F6,KEY_F5,0,KEY_H,KEY_J,KEY_K,KEY_L,KEY_SEMICOLON,KEY_ENTER },
        
        {0,MODIFIERKEY_LEFT_SHIFT,KEY_Z,KEY_X,KEY_C,KEY_V,KEY_B,0,0,0,
            KEY_F7,KEY_F8,KEY_DELETE,KEY_N,KEY_M,KEY_COMMA,KEY_PERIOD,KEY_SLASH,MODIFIERKEY_RIGHT_SHIFT },
        
        {0,MODIFIERKEY_LEFT_GUI,0,0,0,MODIFIERKEY_LEFT_SHIFT<<16|KEY_UP,MODIFIERKEY_LEFT_CTRL,KEY_SPACE,MODIFIERKEY_LEFT_ALT,0,
            0,MODIFIERKEY_LEFT_ALT,KEY_SPACE,MODIFIERKEY_RIGHT_CTRL,KEY_END,KEY_LEFT,KEY_UP,KEY_DOWN,KEY_RIGHT }
    });


SdFat sd;

void setup() {
    KeyMatrix::init();
}

void loop() {
    Display display;

    display.init();

    UI ui(display);
    
    ui.paintText(30, 0, "Start");

    KsKeyboard keyboard;

    ui.paintText(30, 14, "Config");

    if (!sd.begin(10, SPI_HALF_SPEED)) {
        if (sd.card()->errorCode()) {
            char sderr[48];
            sprintf(sderr,"SD Failed : 0x%x", sd.card()->errorCode());
            ui.paintText(30, 28, sderr);
        }
    }
    else
    {
        char sdinfo[48];
        sprintf(sdinfo, "SD OK : %dMB / FAT%d", (int)(0.000512 * sd.card()->cardSize() + 0.5), sd.vol()->fatType());
        ui.paintText(30, 28, sdinfo);

        SdBaseFile myFile;

        if (!myFile.open("test.cfg", O_READ)) {
            ui.paintText(30, 42, "Couldn't open file");
        }
        else
        {
            char data[48];

            myFile.fgets(data, sizeof(data));
            
            ui.paintText(30, 42, data);

            myFile.close();
        }
    }

    KeyHandler keyHandler;
    
    keyHandler.assignLayer(&layer0, 0);
    keyHandler.assignLayer(&layer1, 1);
    keyHandler.assignLayer(&layer2, 2);
    keyHandler.assignLayer(&layer3, 3);

    UsbKeyboard usbKeyboard;
    ActionManager actionManager;

    // actionManager.registerAction(0, Actions::layerModifier(keyboard, 1));
    // actionManager.registerAction(1, Actions::layerModifier(keyboard, 2));
    // actionManager.registerAction(3, Actions::toggleLayer(keyboard, 3));
    // actionManager.registerAction(4, Actions::modifierKey(usbKeyboard, MODIFIERKEY_LEFT_SHIFT, KEY_MINUS));

    actionManager.registerAction(
        2,
        [&](const ActionContext& context)
        {
            if (context.state == KeyState::kPressed)
            {
                // displayDebug = !displayDebug;
                
                // if (!displayDebug)
                // {
                //     display.clear();
                // }

                display.clear();
            }
        });

    actionManager.registerAction(
        5,
        [&](const ActionContext& context)
        {
            if (context.state == KeyState::kPressed)
            {
                ui.menu(keyboard, keyHandler);
            }
        });

    actionManager.registerAction(
        9,
        [&display,&ui](const ActionContext& context)
        {
            if (context.taps == 2)
            {
                display.clear();
                CtrlUtil::bootloader();
            }
        });

    auto callback([&](const KeyHandler::Event& event)
    {
        KeyId keyId(event.keyId);

        if (keyId.type() == KeyId::kModifier)
        {
            if (event.state != KeyState::kReleased)
            {
                usbKeyboard.setModifier(1 << keyId.value());
            }

            if (event.state != KeyState::kHeld)
            {
                usbKeyboard.markDirty();
            }
        }
        else if (keyId.type() == KeyId::kKey)
        {
            if (event.state != KeyState::kReleased)
            {
                usbKeyboard.setKey(keyId.value());
            }
                              
            if (event.state != KeyState::kHeld)
            {
                usbKeyboard.markDirty();
            }
        }
        else if (keyId.type() == KeyId::kAction)
        {
            actionManager.fireAction(keyId.value(),
                                     ActionContext(event.state,
                                                   event.taps));
        }
    });

    while (1)
    {
        if (keyHandler.poll(keyboard, callback))
        {
            usbKeyboard.update();
        }

        // if (displayDebug) 
        // {
        //     sprintf(outStr,"|%4.4x%4.4x%4.4x%4.4x%4.4x|",
        //             (int)matrixA.state()[0].data(),
        //             (int)matrixA.state()[1].data(),
        //             (int)matrixA.state()[2].data(),
        //             (int)matrixA.state()[3].data(),
        //             (int)matrixA.state()[4].data());
        //     ui.paintText(48, 0, outStr);
            
        //     sprintf(outStr,"|%4.4x%4.4x%4.4x%4.4x%4.4x|",
        //             (int)matrixB.state()[0].data(),
        //             (int)matrixB.state()[1].data(),
        //             (int)matrixB.state()[2].data(),
        //             (int)matrixB.state()[3].data(),
        //             (int)matrixB.state()[4].data());
        //     ui.paintText(48, 14, outStr);

        //     sprintf(outStr,"%d / %d ",
        //             (int)debounceA.filtered(),
        //             (int)debounceB.filtered());
        //     ui.paintText(60, 42, outStr);
        // }

    }
}
