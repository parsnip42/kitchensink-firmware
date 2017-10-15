#undef min
#undef max

#include "actionprocessor.h"
#include "keyboardstate.h"
#include "keysource.h"
#include "smartkeyprocessor.h"
#include "macroprocessor.h"
#include "multikeyprocessor.h"
#include "layerprocessor.h"
#include "keyboardstateutil.h"
#include "eventmanager.h"
#include "topleveleventstage.h"
#include "crypto/entropypool.h"
#include "hardware/compositekeyhardware.h"
#include "hardware/keyboardplate.h"
#include "serialize/serializer.h"
#include "types/datarefinstream.h"
#include "event/compositeeventsource.h"

#include <bluefruitkeyboard.h>
#include <gpiokeyset.h>

void setup()
{
}

void loop()
{
    KeyboardState keyboardState;

    static const char* const LayoutConfig =
    "[layer 0]\n"
    "name=Default\n"
    "row=KUp KDown KLeft KRight L1 KP K1 K5 KEnter KS KD KF KZ KX KC KV\n"
    
    "[layer 1]\n"
    "name=Alt\n"
    "row=_ _ _ _ _ _ _ _ KTab KEsc _ MD0 _ _ _\n";

    {
        DataRefInStream is(LayoutConfig);
        Serializer<LayerStack> s;

        s.deserialize(is, keyboardState.layerStack);
    }

    static const char* const MacroConfig =
    "[macro 0]\n"
    "name=Alt+F4\n"
    "shortcut=\n"
    "type=2\n"
    "content=KLAlt KF4\n"
    
    "[macro 1]\n";

    {
        DataRefInStream is(MacroConfig);
        Serializer<MacroSet> s;
    
        s.deserialize(is, keyboardState.macroSet);
    }

    BluefruitKeyboard usbKeyboard;

    TimerManager timerManager;
    
    ToplevelEventStage toplevel;

    EntropyPool entropyPool;
    
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

    std::array<uint8_t, 16> pins({ 14, 15, 16, 17, 18, 19, 0, 1, 12, 11, 10, 9, 6, 5, 21, 20 });

    GPIOKeySet gpioKeys(pins.begin(), pins.end());

    KeyboardPlate<GPIOKeySet, 16, 1> keyboard(gpioKeys,
                                              {{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }},
                                              {{ 0 }});

    KeySource keySource(keyboard,
                        keyboardState.layerStack);

    layerProcessor.keySource = &keySource;
    
    CompositeEventSource<2> eventSource({ &keySource, &timerManager });
    
    EventManager eventManager(eventSource,
                              multiKeyProcessor,
                              toplevel,
                              usbKeyboard);

    while (true)
    {
        eventManager.poll(usbKeyboard);
    }
}
