#include "actionprocessor.h"
#include "defaultlayers.h"
#include "display.h"
#include "keydispatcher.h"
#include "kskeyboard.h"
#include "keyprocessor.h"
#include "usbkeyboard.h"

#include "ui/surface.h"
#include "ui/home.h"

#include <SdFat.h>

SdFat sd;

void setup() {
    KeyMatrix::setup();
}

void loop() {
    Display display;

    display.init();

    UI::Surface surface(display);
    
    surface.paintText(30, 0, "Start");

    KsKeyboard keyboard;

    keyboard.init();
    
    surface.paintText(30, 14, "Config");

    if (!sd.begin(10, SPI_HALF_SPEED)) {
        if (sd.card()->errorCode()) {
            char sderr[48];
            sprintf(sderr,"SD Failed : 0x%x", sd.card()->errorCode());
            surface.paintText(30, 28, sderr);
        }
    }
    else
    {
        char sdinfo[48];
        sprintf(sdinfo, "SD OK : %dMB / FAT%d", (int)(0.000512 * sd.card()->cardSize() + 0.5), sd.vol()->fatType());
        surface.paintText(30, 28, sdinfo);

        SdBaseFile myFile;

        if (!myFile.open("test.cfg", O_READ)) {
            surface.paintText(30, 42, "Couldn't open file");
        }
        else
        {
            char data[48];

            myFile.fgets(data, sizeof(data));
            
            surface.paintText(30, 42, data);

            myFile.close();
        }
    }

    display.clear();

    KeyDispatcher keyDispatcher(keyboard);
    
    DefaultLayers::init(keyDispatcher);

    UsbKeyboard usbKeyboard;

    // UI::Home home(surface,
    //               modifierProcessor.modifierSet());

    KeyProcessor keyProcessor(keyDispatcher);

    ActionProcessor actionProcessor(keyProcessor,
                                    surface);

    while (1)
    {
        keyProcessor.poll();
        
        if (keyProcessor.hasEvent())
        {
            auto event(keyProcessor.popEvent());

            const auto& keyId(event.keyId);

            if (keyId.type() == KeyId::Type::kKey)
            {
                usbKeyboard.processKey(keyId.value(), event.pressed);
            }
            else if (keyId.type() == KeyId::Type::kAction)
            {
                actionProcessor.processEvent(event);
            }
        }
        
        // home.update();
        // home.paint();
    }
}
