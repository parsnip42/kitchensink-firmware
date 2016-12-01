#include "actionprocessor.h"
#include "defaultlayers.h"
#include "display.h"
#include "kskeyboard.h"
#include "keyboardstate.h"
#include "keyprocessor.h"
#include "usbkeyboard.h"

#include "ui/surface.h"
#include "ui/home.h"
#include "ui/text.h"

#include <SdFat.h>

SdFat sd;

void setup() {
    KeyMatrix::setup();
}

void loop() {
    Display display;

    display.init();

    UI::Surface surface(display);

    UI::Text initLog(surface);

    initLog.appendLine("Start");
    
    KsKeyboard keyboard;

    keyboard.init();

    initLog.appendLine("Configure");

    if (!sd.begin(10, SPI_HALF_SPEED)) {
        if (sd.card()->errorCode()) {
            char sderr[48];
            sprintf(sderr,"SD Failed : 0x%x", sd.card()->errorCode());
            initLog.appendLine(sderr);
        }
    }
    else
    {
        char sdinfo[48];
        sprintf(sdinfo, "SD OK : %dMB / FAT%d", (int)(0.000512 * sd.card()->cardSize() + 0.5), sd.vol()->fatType());
        initLog.appendLine(sdinfo);

        SdBaseFile myFile;

        if (!myFile.open("test.cfg", O_READ)) {
            initLog.appendLine("Couldn't open file");
        }
        else
        {
            char data[48];

            myFile.fgets(data, sizeof(data));
            
            initLog.appendLine(data);

            myFile.close();
        }
    }
    
    
    UsbKeyboard usbKeyboard;

    KeyboardState keyboardState;

    DefaultLayers::init(keyboardState.layerStack);
    
    keyboardState.modifierSet[0] = Modifier("Gm0", KeyId::Layer(3));
    keyboardState.modifierSet[1] = Modifier("Gm1", KeyId::Layer(4));
    keyboardState.modifierSet[2] = Modifier("Gm2", KeyId::Layer(5));
    keyboardState.modifierSet[3] = Modifier("KSP", KeyId::Layer(6));
    keyboardState.modifierSet[5] = Modifier("LShft", 0xe1);
    keyboardState.modifierSet[6] = Modifier("RShft", 0xe5);

    keyboardState.macroSet.setMacro(0, {
            KeyEvent(KeyId(KEY_LEFT_BRACE)),
            KeyEvent(KeyId(0xe1)),
            });

    keyboardState.macroSet.setMacro(1, {
            KeyEvent(KeyId(KEY_RIGHT_BRACE)),
            KeyEvent(KeyId(0xe1)),
            });

    keyboardState.macroSet.setMacro(2, {
            KeyEvent(KeyId(KEY_9)),
            KeyEvent(KeyId(0xe1)),
            });

    keyboardState.macroSet.setMacro(3, {
            KeyEvent(KeyId(KEY_0)),
            KeyEvent(KeyId(0xe1)),
            });

    keyboardState.macroSet.setMacro(4, {
            KeyEvent(KeyId(KEY_COMMA)),
            KeyEvent(KeyId(0xe1)),
            });

    keyboardState.macroSet.setMacro(5, {
            KeyEvent(KeyId(KEY_PERIOD)),
            KeyEvent(KeyId(0xe1)),
            });
    
    keyboardState.macroSet.setMacro(6, {
            KeyEvent(KeyId(KEY_SPACE)),
            KeyEvent(KeyId(0xe0)),
            });

    keyboardState.macroSet.setMacro(10, {
            KeyEvent(KeyId(KEY_MINUS)),
            KeyEvent(KeyId(0xe1)),
            });

    keyboardState.macroSet.setMacro(11, {
            KeyEvent(KeyId(KEY_MINUS)),
            KeyEvent(KeyId(0xe1)),
            });

    keyboardState.macroSet.setMacro(15, {
            KeyEvent(KeyId(KEY_COMMA)),
            KeyEvent(KeyId(0xe2)),
            });
    keyboardState.macroSet.setMacro(16, {
            KeyEvent(KeyId(KEY_PERIOD)),
            KeyEvent(KeyId(0xe2)),
            });
    keyboardState.macroSet.setMacro(17, {
            KeyEvent(KeyId(KEY_L)),
            KeyEvent(KeyId(0xe2)),
            });    
    keyboardState.macroSet.setMacro(18, {
            KeyEvent(KeyId(KEY_F5)),
            KeyEvent(KeyId(0xe2)),
            });
    keyboardState.macroSet.setMacro(19, {
            KeyEvent(KeyId(KEY_F9)),
            KeyEvent(KeyId(0xe2)),
            });

    UI::Home home(surface,
                  keyboardState.modifierSet);

    KeyProcessor keyProcessor(keyboard,
                              keyboardState);

    ActionProcessor actionProcessor(keyProcessor,
                                    surface);

    while (1)
    {
        keyProcessor.poll(
            [&](const KeyEvent& event)
            {
                const auto& keyId(event.keyId);

                if (keyId.type() == KeyId::Type::kKey)
                {
                    usbKeyboard.processKey(keyId.value(), event.pressed);
                }
                else if (keyId.type() == KeyId::Type::kAction)
                {
                    actionProcessor.processEvent(event);
                }
            },
            [&]()
            {
                home.update();
            });
                                
//        home.paint();
    }
}
