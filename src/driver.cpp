#include "actionprocessor.h"
#include "defaultprofile.h"
#include "display.h"
#include "kskeyboard.h"
#include "keyboardstate.h"
#include "keyprocessor.h"
#include "usbkeyboard.h"

#include "storage/storage.h"

#include "ui/surface.h"
#include "ui/home.h"
#include "ui/text.h"

#include "types/strbuf.h"


void setup()
{
    KeyMatrix::setup();
}

void loop()
{
    Display display;

    display.init();

    UI::Surface surface(display);

    UI::Text initLog(surface);

    initLog.appendLine("Start");
    
    initLog.appendLine("Configure");

    Storage storage;
    
    if (storage.state())
    {
        StrBuf<48> sdErr;
        
        sdErr.appendStr("SD Failed : ")
             .appendInt(storage.state());

        initLog.appendLine(sdErr);
    }
    else
    {
        StrBuf<48> sdInfo;

        sdInfo.appendStr("SD OK : ")
              .appendInt(storage.capacityMb())
              .appendStr("MB / FAT")
              .appendInt(storage.fatType());
        
        initLog.appendLine(sdInfo);

    }

    StrBuf<5> str;

    initLog.appendLine(str);

    //surface.clear();
    
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
                                    usbKeyboard,
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
