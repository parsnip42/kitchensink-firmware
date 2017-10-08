#include <dummy.h>

#undef min
#undef max

#include "actionprocessor.h"
#include "defaultprofile.h"
#include "hardware/display.h"
#include "hardware/dmoled32display.h"
#include "kskeyboard.h"
#include "keyboardstate.h"
#include "keysource.h"
#include "hardware/teensyusbkeyboard.h"
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
#include "crypto/entropypool.h"

#include "types/strbuf.h"

void setup()
{
    KeyMatrix::setup();
}

void loop()
{
    DMOLED32Display display;

    Surface surface(display);
    
    TeensyUsbKeyboard usbKeyboard;

    EntropyPool entropyPool;
    
    KsKeyboard keyboard(entropyPool);

    KeyboardState keyboardState;
    
    DefaultProfile::init(keyboardState);
    KeyboardStateUtil::load(keyboardState);
    
    Timer timer;
    
    ToplevelEventStage toplevel(usbKeyboard);
    
    ActionProcessor actionProcessor(keyboardState,
                                    entropyPool,
                                    toplevel);

    LayerProcessor layerProcessor(actionProcessor);
    
    MacroProcessor macroProcessor(keyboardState.macroSet,
                                  keyboardState.secureMacroSet,
                                  keyboardState.globalConfig,
                                  timer,
                                  layerProcessor);

    SmartKeyProcessor smartKeyProcessor(keyboardState.smartKeySet,
                                        macroProcessor);

    MultiKeyProcessor multiKeyProcessor(keyboardState.multiKeySet,
                                        keyboardState.globalConfig,
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
                                keyboardState,
                                entropyPool);

    screenManager.poll();

    // while (true)
    // {
    //     eventManager.poll(usbKeyboard);
    // }
}
