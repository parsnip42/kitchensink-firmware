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

#include "storage/storage.h"

#include "types/strutil.h"

#include "ui/surface.h"
#include "ui/home.h"
#include "ui/screenstack.h"
#include "ui/screenmanager.h"

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

    MacroProcessor secureMacroProcessor(KeyId::Type::kSMacro,
                                        keyboardState.secureMacroSet,
                                        timer,
                                        layerProcessor);

    MacroProcessor macroProcessor(KeyId::Type::kMacro,
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
    
    EventManager eventManager(timer,
                              keySource,
                              multiKeyProcessor,
                              toplevel,
                              usbKeyboard);
    
    ScreenManager screenManager(surface,
                                eventManager,
                                keyboardState);

    screenManager.poll(usbKeyboard);
}
