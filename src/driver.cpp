#include "actionprocessor.h"
#include "defaultprofile.h"
#include "hardware/display.h"
#include "kskeyboard.h"
#include "keyboardstate.h"
#include "keysource.h"
#include "usbkeyboard.h"
#include "serialize/serializer.h"
#include "serialize/iniformat.h"
#include "smartkeyprocessor.h"
#include "macroprocessor.h"
#include "multikeyprocessor.h"
#include "layerprocessor.h"
#include "ledsource.h"

#include "storage/storage.h"

#include "types/strutil.h"

#include "ui/surface.h"
#include "ui/screenstack.h"
#include "ui/screenmanager.h"
#include "ui/homescreen.h"

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
    
    UsbKeyboard usbKeyboard;
    
    KsKeyboard keyboard;

    KeyboardState keyboardState;
    
    DefaultProfile::init(keyboardState);

    {
        Storage storage;
        
        auto is(storage.read(Storage::Region::Macro));
        Serializer<MacroSet> s;
        
        s.deserialize(is, keyboardState.macroSet);
    }

    Timer timer;
    
    ToplevelEventStage toplevel(usbKeyboard);
    
    ActionProcessor actionProcessor(toplevel);

    LayerProcessor layerProcessor(actionProcessor);

    MacroProcessor secureMacroProcessor(Event::Type::kSMacro,
                                        keyboardState.secureMacroSet,
                                        timer,
                                        layerProcessor);

    MacroProcessor macroProcessor(Event::Type::kMacro,
                                  keyboardState.macroSet,
                                  timer,
                                  secureMacroProcessor);

    SmartKeyProcessor smartKeyProcessor(keyboardState.smartKeySet,
                                        macroProcessor);

    MultiKeyProcessor multiKeyProcessor(keyboardState.multiSet,
                                        timer,
                                        smartKeyProcessor);

    KeySource keySource(keyboard,
                        keyboardState.layerStack);

    layerProcessor.keySource = &keySource;

    LedSource ledSource;
    
    EventManager eventManager(timer,
                              keySource,
                              ledSource,
                              multiKeyProcessor,
                              toplevel,
                              usbKeyboard);
    
    HomeScreen homeScreen(eventManager.timer,
                          keyboardState.smartKeySet,
                          usbKeyboard);
            
    ScreenManager screenManager(surface,
                                eventManager,
                                keyboardState,
                                homeScreen);

    screenManager.poll(usbKeyboard);
}
