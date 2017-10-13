#include "actionprocessor.h"
#include "defaultprofile.h"
#include "hardware/dmoled32display.h"
#include "kskeyboard.h"
#include "keyboardstate.h"
#include "keysource.h"
#include "hardware/i2ckeymatrix.h"
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

#include <teensyusbkeyboard.h>
#include <teensyledsource.h>

void setup()
{
    I2CKeyMatrix::setup();
}

void loop()
{
    DMOLED32Display display;

    TeensyUsbKeyboard usbKeyboard;

    EntropyPool entropyPool;
    
    KsKeyboard keyboard(entropyPool);

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
