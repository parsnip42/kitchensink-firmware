#include "actionprocessor.h"
#include "defaultprofile.h"
#include "display.h"
#include "kskeyboard.h"
#include "keyboardstate.h"
#include "keyprocessor.h"
#include "usbkeyboard.h"
#include "serialize/serializer.h"

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
    
    StrBuf<128> str;

    {
        auto iStream(storage.read(Storage::Region::kConfig));

        do
        {
            iStream.readToken(str,"\r\n\t");
            initLog.appendLine(str);
        }
        while (!str.empty());
    }
    

    //surface.clear();
    
    UsbKeyboard usbKeyboard;
    
    KsKeyboard keyboard;

    keyboard.init();

    KeyboardState keyboardState;

    DefaultProfile::init(keyboardState);

    {
        auto os(storage.write(Storage::Region::kConfig));
        
        {
            Serializer<Layer> s;

            for (const auto& layer : keyboardState.layerStack)
            {
                s.serialize(layer, os);
            }
        }
        
        {
            Serializer<MacroSet::Macro> s;

            const auto& macroSet(keyboardState.macroSet);
            
            for (std::size_t i(0); i < macroSet.size(); ++i)
            {
                s.serialize(macroSet[i], os);
            }
        }
    }

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
