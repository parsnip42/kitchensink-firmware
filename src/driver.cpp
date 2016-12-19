#include "actionprocessor.h"
#include "defaultprofile.h"
#include "display.h"
#include "kskeyboard.h"
#include "keyboardstate.h"
#include "keyprocessor.h"
#include "usbkeyboard.h"

#include "ui/surface.h"
#include "ui/home.h"
#include "ui/text.h"

#include "types/strbuf.h"

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
    
    initLog.appendLine("Configure");

    if (!sd.begin(10, SPI_HALF_SPEED))
    {
        if (sd.card()->errorCode())
        {
            Types::StrBuf<48> sdErr;

            sdErr.appendStr("SD Failed : ")
                 .appendInt(sd.card()->errorCode());
            
            initLog.appendLine(sdErr);
        }
    }
    else
    {
        Types::StrBuf<48> sdInfo;

        sdInfo.appendStr("SD OK : ")
              .appendInt(static_cast<int>((0.000512 * sd.card()->cardSize() + 0.5)))
              .appendStr("MB / FAT")
              .appendInt(sd.vol()->fatType());
        
        initLog.appendLine(sdInfo);

        SdBaseFile myFile;

        if (!myFile.open("test.cfg", O_READ))
        {
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

    Types::StrBuf<5> str;

    initLog.appendLine(str);

    surface.clear();
    
    UsbKeyboard usbKeyboard;
    
    KsKeyboard keyboard;

    keyboard.init();

    KeyboardState keyboardState;

    DefaultProfile::init(keyboardState);
    
    UI::Home home(surface,
                  keyboardState);

    KeyProcessor keyProcessor(keyboard,
                              keyboardState);

    ActionProcessor actionProcessor(keyProcessor,
                                    keyboardState,
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
                                
        home.paint();
    }
}
