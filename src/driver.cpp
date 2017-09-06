#include "actionprocessor.h"
#include "defaultprofile.h"
#include "hardware/display.h"
#include "kskeyboard.h"
#include "keyboardstate.h"
#include "keysource.h"
#include "usbkeyboard.h"
#include "smartkeyprocessor.h"
#include "macroprocessor.h"
#include "multikeyprocessor.h"
#include "layerprocessor.h"
#include "ledsource.h"
#include "types/strutil.h"
#include "keyboardstateutil.h"

#include "ui/surface.h"
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
    KeyboardStateUtil::load(keyboardState);

    Timer timer;
    
    ToplevelEventStage toplevel(usbKeyboard);
    
    ActionProcessor actionProcessor(toplevel);

    LayerProcessor layerProcessor(actionProcessor);

    MacroProcessor secureMacroProcessor(keyboardState.secureMacroSet,
                                        timer,
                                        layerProcessor);

    MacroProcessor macroProcessor(keyboardState.macroSet,
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
    
    ScreenManager screenManager(surface,
                                eventManager,
                                keyboardState);

    screenManager.poll();
}
