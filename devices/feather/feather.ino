#undef min
#undef max

#include "actionprocessor.h"
#include "defaultprofile.h"
#include "afili9431display.h"
#include "keyboardstate.h"
#include "keysource.h"
#include "hardware/arduinousbkeyboard.h"
#include "smartkeyprocessor.h"
#include "macroprocessor.h"
#include "multikeyprocessor.h"
#include "layerprocessor.h"
#include "keyboardstateutil.h"
#include "ui/screenmanager.h"
#include "eventmanager.h"
#include "topleveleventstage.h"
#include "crypto/entropypool.h"
#include "hardware/compositekeyhardware.h"

void setup()
{
}

void loop()
{
    ArduinoUsbKeyboard usbKeyboard;

    EntropyPool entropyPool;
    
    CompositeKeyHardware<0> keyboard({});
    
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

    EventManager eventManager(keySource,
                              multiKeyProcessor,
                              toplevel,
                              usbKeyboard);

    AFILI9431Display display;

    eventManager.processEvent(ScreenEvent::create(ScreenEvent::Type::kMenu, 0));

    ScreenManager screenManager(display,
                                eventManager,
                                timerManager,
                                keyboardState,
                                keyboard,
                                entropyPool);

    screenManager.poll();
}
