#include "actionprocessor.h"
#include "defaultprofile.h"
#include "display.h"
#include "kskeyboard.h"
#include "keyboardstate.h"
#include "keyprocessor.h"
#include "usbkeyboard.h"
#include "serialize/serializer.h"

#include "storage/storage.h"

#include "types/strutil.h"

#include "ui/surface.h"
#include "ui/home.h"
#include "ui/text.h"

#include "types/strbuf.h"
#include "types/strostream.h"


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

        StrOStream out(sdErr);
        
        out.appendStr("SD Failed : ")
           .appendInt(storage.state());

        initLog.appendLine(sdErr);
    }
    else
    {
        StrBuf<48> sdInfo;
        StrOStream out(sdInfo);
        
        out.appendStr("SD OK : ")
           .appendInt(storage.capacityMb())
           .appendStr("MB / FAT")
           .appendInt(storage.fatType());
        
        initLog.appendLine(sdInfo);
    }
    

    //surface.clear();
    
    UsbKeyboard usbKeyboard;
    
    KsKeyboard keyboard;

    keyboard.init();

    KeyboardState keyboardState;








    
    DefaultProfile::init(keyboardState);

    {
        auto os(storage.write(Storage::Region::Config));
        
        {
            Serializer<Layer> s;

            s.serialize(keyboardState.layerStack[0], os);
        }
    }
    
    {
        StrBuf<200> line;
        StrOStream ostream(line);
        
        auto is(storage.read(Storage::Region::Config));
        
        is.readToken(ostream, "\r\n");

        if (line == "[Layer]")
        {
            Serializer<Layer> s;
            
            s.deserialize(is, keyboardState.layerStack[0]);
        }
    }

    {
        auto os(storage.write(Storage::Region::Config));
        
        {
            Serializer<Layer> s;

            s.serialize(keyboardState.layerStack[0], os);
        }
        
    }

    {
        auto is(storage.read(Storage::Region::Config));

        StrBuf<200> line;
        StrOStream ostream(line);
        
        do
        {
            line.clear();
            is.readToken(ostream, "\r\n");
            initLog.appendLine(line);
        } while (!line.empty());
    }
    
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
