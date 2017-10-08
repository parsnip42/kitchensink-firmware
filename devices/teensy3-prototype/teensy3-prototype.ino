#include "actionprocessor.h"
#include "defaultprofile.h"
#include "hardware/dmoled32display.h"
#include "kskeyboard.h"
#include "keyboardstate.h"
#include "keysource.h"
#include "hardware/i2ckeymatrix.h"
#include "hardware/teensyusbkeyboard.h"
#include "smartkeyprocessor.h"
#include "macroprocessor.h"
#include "multikeyprocessor.h"
#include "layerprocessor.h"
#include "ledsource.h"
#include "keyboardstateutil.h"
#include "ui/screenmanager.h"
#include "eventmanager.h"
#include "topleveleventstage.h"
#include "crypto/entropypool.h"

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

    LedSource ledSource;
    
    EventManager eventManager(timerManager,
                              keySource,
                              ledSource,
                              multiKeyProcessor,
                              toplevel,
                              usbKeyboard);
    
    ScreenManager screenManager(display,
                                eventManager,
                                keyboardState,
                                entropyPool);

    screenManager.poll();
}
