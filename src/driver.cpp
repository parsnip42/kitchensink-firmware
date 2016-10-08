
#include "actioncontext.h"
#include "actionmanager.h"
#include "actions.h"
#include "ctrlutil.h"
#include "defaultlayers.h"
#include "display.h"
#include "eventqueue.h"
#include "keyhandler.h"
#include "kskeyboard.h"
#include "layer.h"
#include "modifierset.h"
#include "ui.h"
#include "usbkeyboard.h"

#include <SdFat.h>

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

    display.clear();

    KeyHandler keyHandler(keyboard);
    
    DefaultLayers::init(keyHandler);

    UsbKeyboard usbKeyboard;
    ActionManager actionManager;

    EventQueue eventQueue;
    
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

                // display.clear();

                // eventQueue.pushBack(KEY_T);
                // eventQueue.pushBack(KEY_H);
                // eventQueue.pushBack(KEY_I);
                // eventQueue.pushBack(KEY_S);
                // eventQueue.pushBack(KEY_SPACE);
                // eventQueue.pushBack(KEY_I);
                // eventQueue.pushBack(KEY_S);
                // eventQueue.pushBack(KEY_SPACE);
                // eventQueue.pushBack(KEY_A);
                // eventQueue.pushBack(KEY_SPACE);
                // eventQueue.pushBack(KEY_T);
                // eventQueue.pushBack(KEY_E);
                // eventQueue.pushBack(KEY_S);
                // eventQueue.pushBack(KEY_T);

            }
        });

    actionManager.registerAction(
        5,
        [&](const ActionContext& context)
        {
            if (context.state == KeyState::kPressed)
            {
                ui.menu(keyHandler);
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

    auto callback([&](const KeyEvent& event)
    {
        eventQueue.pushBack(event);
    });
    
    ModifierSet modifierSet;

    while (1)
    {
        keyHandler.poll(eventQueue);

        while (!eventQueue.empty())
        {
            auto event(eventQueue.pop());

            const auto& keyId(event.keyId);

            if (keyId.type() == KeyId::kModifier)
            {
                if (keyId.value() < 10)
                {
                    usbKeyboard.processModifier(keyId.value(), event.state);
                }
                else
                {
                    int layerId(keyId.value() - 10);
                    bool state(event.state == KeyState::kPressed);

                    keyHandler.setLayer(layerId, state, eventQueue);
                }
            }
            else if (keyId.type() == KeyId::kKey)
            {
                usbKeyboard.processKey(keyId.value(), event.state);
            }
            else if (keyId.type() == KeyId::kAction)
            {
                actionManager.fireAction(keyId.value(),
                                         ActionContext(event.state,
                                                       event.taps));
            }
        }

        // char outStr[129];
        // sprintf(outStr,"|%d %d %d %d|",
        //         (int)keyHandler.mModifierSet[0].mRefCount,
        //         (int)keyHandler.mModifierSet[1].mRefCount,
        //         (int)keyHandler.mModifierSet[2].mRefCount,
        //         (int)keyHandler.mModifierSet[3].mRefCount);
        // ui.paintText(48, 0, outStr);


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
