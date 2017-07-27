#include "actionprocessor.h"
#include "delayprocessor.h"
#include "defaultprofile.h"
#include "display.h"
#include "kskeyboard.h"
#include "keyboardstate.h"
#include "keyprocessor.h"
#include "usbkeyboard.h"
#include "serialize/serializer.h"
#include "serialize/iniformat.h"

#include "storage/storage.h"

#include "types/strutil.h"

#include "ui/surface.h"
#include "ui/home.h"
#include "ui/text.h"
#include "ui/screenstack.h"

#include "keyeventbuffer.h"
#include "eventmanager.h"
#include "topleveleventstage.h"

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

    Surface surface(display);

    Text initLog(surface);

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
    

    surface.clear();
    
    UsbKeyboard usbKeyboard;
    
    KsKeyboard keyboard;

    keyboard.init();

    KeyboardState keyboardState;








    
    DefaultProfile::init(keyboardState);

    // {
    //     auto os(storage.write(Storage::Region::Config));

    //     for (const auto& layer : keyboardState.layerStack)
    //     {
    //         Serializer<Layer> s;

    //         os.write("[Layer]\n");
    //         s.serialize(layer, os);
    //         os.write("\n");
    //     }
    // }
    
    // {
    //     StrBuf<200> line;
    //     StrOStream ostream(line);
        
    //     auto is(storage.read(Storage::Region::Config));

    //     auto& layerStack(keyboardState.layerStack);
    //     std::size_t layerCount(0);
        
    //     while(is.readLine(ostream))
    //     {
    //         if (line == "[Layer]" && layerCount < layerStack.size())
    //         {
    //             Serializer<Layer> s;
                
    //             s.deserialize(is, layerStack[layerCount++]);
    //         }

    //         line.clear();
    //     }
    // }

    // {
    //     auto os(storage.write(Storage::Region::Config));
    //     const auto& macroSet(keyboardState.macroSet);
        
    //     for (std::size_t i(0); i < macroSet.size(); ++i)
    //     {
    //         Serializer<MacroSet::Macro> s;
            
    //         os.write("[Macro]\n");
    //         s.serialize(macroSet[i], os);
    //         os.write("\n");
    //     }
    // }


    // {
    //     auto is(storage.read(Storage::Region::Config));
    //     StrBuf<200> line;6

    //     while (is.readLine(line))
    //     {
    //         initLog.appendLine(line);
    //     }
    // }
    
    {
        auto is(storage.read(Storage::Region::Macro));
        Serializer<MacroSet> s;
        
        s.deserialize(is, keyboardState.macroSet);
    }

    
     // DefaultProfile::init(keyboardState);


    Timer timer;
    
    ToplevelEventStage toplevel(usbKeyboard);
    
    ActionProcessor actionProcessor(keyboardState,
                                    toplevel);
    
    MacroProcessor macroProcessor(keyboardState.macroSet,
                                  timer,
                                  actionProcessor);

    LockProcessor lockProcessor(keyboardState.lockSet,
                                macroProcessor);
    
    MultiProcessor multiProcessor(keyboardState.multiSet,
                                  timer,
                                  macroProcessor);

    KeyProcessor keyProcessor(keyboard,
                              keyboardState.layerStack);
    
    EventManager eventManager(timer,
                              keyProcessor,
                              multiProcessor,
                              toplevel,
                              usbKeyboard);
    
    ScreenStack screenStack(keyboardState,
                            eventManager,
                            surface,
                            usbKeyboard);

    while (1)
    {
        eventManager.poll(screenStack);
    }
}
