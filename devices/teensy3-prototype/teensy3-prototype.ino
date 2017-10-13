#include "actionprocessor.h"
#include "defaultprofile.h"
#include "keyboardstate.h"
#include "keysource.h"
#include "smartkeyprocessor.h"
#include "macroprocessor.h"
#include "multikeyprocessor.h"
#include "layerprocessor.h"
#include "keyboardstateutil.h"
#include "ui/screenmanager.h"
#include "eventmanager.h"
#include "topleveleventstage.h"
#include "crypto/entropypool.h"
#include "event/compositeeventsource.h"
#include "hardware/compositekeyhardware.h"

#include <teensyusbkeyboard.h>
#include <teensyledsource.h>
#include <dmoled32display.h>
#include <i2ckeymatrix.h>

#include "keyboardplate.h"

void setup()
{
    I2CKeyMatrix::setup();
}

void loop()
{
    DMOLED32Display display;

    EntropyPool entropyPool;

    KeyboardPlate leftPlate(0x20, 0x7c00, 0x3ff,
                            {{ 4, 3, 2, 1, 0 }},
                            {{ 0, 1, 2, 3, 4, 5, 6, 7, 9, 8, 10, 11, 12, 13, 14, 15 }},
                            entropyPool);

    KeyboardPlate rightPlate(0x21, 0x3e00, 0xc0ff,
                             {{ 0, 1, 2, 3, 4}},
                             {{ 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 11, 10 }},
                             entropyPool);
    
    CompositeKeyHardware<2> keyboard({ &leftPlate, &rightPlate });

    KeyboardState keyboardState;
    
    DefaultProfile::init(keyboardState);
    KeyboardStateUtil::load(keyboardState);
    
    TimerManager timerManager;
    
    ToplevelEventStage toplevel;
    
    ActionProcessor actionProcessor(keyboardState,
                                    entropyPool,
                                    toplevel);

    LayerProcessor layerProcessor(actionProcessor);
    
    MacroProcessor macroProcessor(keyboardState.macroSet,
                                  keyboardState.secureMacroSet,
                                  keyboardState.globalConfig,
                                  timerManager,
                                  layerProcessor);

    SmartKeyProcessor smartKeyProcessor(keyboardState.smartKeySet,
                                        macroProcessor);

    MultiKeyProcessor multiKeyProcessor(keyboardState.multiKeySet,
                                        keyboardState.globalConfig,
                                        timerManager,
                                        smartKeyProcessor);

    KeySource keySource(keyboard,
                        keyboardState.layerStack);

    layerProcessor.keySource = &keySource;

    TeensyUsbKeyboard usbKeyboard;
    TeensyLedSource ledSource;

    CompositeEventSource<3> eventSource({ &keySource, &ledSource, &timerManager });
    
    EventManager eventManager(eventSource,
                              multiKeyProcessor,
                              toplevel,
                              usbKeyboard);
    
    ScreenManager screenManager(display,
                                eventManager,
                                timerManager,
                                keyboardState,
                                keyboard,
                                entropyPool);

    screenManager.poll();
}
