#include "actionprocessor.h"
#include "ctrlutil.h"
#include "defaultlayers.h"
#include "display.h"
#include "eventqueue.h"
#include "keyhandler.h"
#include "kskeyboard.h"
#include "layer.h"
#include "macroprocessor.h"
#include "modifierprocessor.h"
#include "usbkeyboard.h"

#include "ui/surface.h"
#include "ui/home.h"

#include <SdFat.h>

namespace
{

// class MainMenu : public UIMenu::Data
// {
// public:
//     virtual UIMenu::Entry entry(std::size_t n)
//     {
//         UIMenu::Entry entries[] = {
//             UIMenu::Entry("            Bootloader          ", KeyEvent(KeyId::Action(9), KeyState::kPressed, 2)),
//             UIMenu::Entry("              Macros            ", KeyEvent(KeyId::Action(5))),
//             UIMenu::Entry("          Configuration         ", KeyEvent(KeyId::Action(5))),
//             UIMenu::Entry("             System             ", KeyEvent(KeyId::Action(5))),
//             UIMenu::Entry("             Test 0             ", KeyEvent(KeyId::Action(5))),
//             UIMenu::Entry("             Test 1             ", KeyEvent(KeyId::Action(5))),
//             UIMenu::Entry("             Test 2             ", KeyEvent(KeyId::Action(5))),
//             UIMenu::Entry("             Test 3             ", KeyEvent(KeyId::Action(5))),
//             UIMenu::Entry("             Test 4             ", KeyEvent(KeyId::Action(5))),
//             UIMenu::Entry("             Test 5             ", KeyEvent(KeyId::Action(5))),
//             UIMenu::Entry("             Test 6             ", KeyEvent(KeyId::Action(5))),
//             UIMenu::Entry("             Test 7             ", KeyEvent(KeyId::Action(5)))
//         };

//         return entries[n];
//     }
    
//     virtual std::size_t size()
//     {
//         return 12;
//     }
// };

// class MenuB : public UIMenu::Data
// {
// public:
//     virtual UIMenu::Entry entry(std::size_t n)
//     {
//         UIMenu::Entry entries[] = {
//             UIMenu::Entry("            Bootloader          ", KeyEvent(KeyId::Action(9), KeyState::kPressed, 2)),
//             UIMenu::Entry("             Display            ", KeyEvent(KeyId::Action(5))),
//             UIMenu::Entry("          Configuration         ", KeyEvent(KeyId::Action(5))),
//             UIMenu::Entry("             System             ", KeyEvent(KeyId::Action(5)))
//         };

//         return entries[n];
//     }
    
//     virtual std::size_t size()
//     {
//         return 4;
//     }
// };

}

SdFat sd;

void setup() {
    KeyMatrix::setup();
}

void loop() {
    Display display;

    display.init();

    UI::Surface surface(display);
    
    surface.paintText(30, 0, "Start");

    KsKeyboard keyboard;

    keyboard.init();
    
    surface.paintText(30, 14, "Config");

    if (!sd.begin(10, SPI_HALF_SPEED)) {
        if (sd.card()->errorCode()) {
            char sderr[48];
            sprintf(sderr,"SD Failed : 0x%x", sd.card()->errorCode());
            surface.paintText(30, 28, sderr);
        }
    }
    else
    {
        char sdinfo[48];
        sprintf(sdinfo, "SD OK : %dMB / FAT%d", (int)(0.000512 * sd.card()->cardSize() + 0.5), sd.vol()->fatType());
        surface.paintText(30, 28, sdinfo);

        SdBaseFile myFile;

        if (!myFile.open("test.cfg", O_READ)) {
            surface.paintText(30, 42, "Couldn't open file");
        }
        else
        {
            char data[48];

            myFile.fgets(data, sizeof(data));
            
            surface.paintText(30, 42, data);

            myFile.close();
        }
    }

    display.clear();

    KeyHandler keyHandler(keyboard);
    
    DefaultLayers::init(keyHandler);

    UsbKeyboard usbKeyboard;
    ActionProcessor actionProcessor;

    EventQueue eventQueue;
    
    actionProcessor.registerAction(
        2,
        [&](const KeyEvent& event,
            EventQueue&     eventQueue)
        {
            if (event.pressed)
            {
                display.clear();
            }
        });
    
    actionProcessor.registerAction(
        5,
        [&](const KeyEvent& event,
            EventQueue&     eventQueue)
        {
        });

    actionProcessor.registerAction(
        9,
        [&](const KeyEvent& event,
            EventQueue&     eventQueue)
        {
            if (event.pressed)
            {
                surface.clear();
                CtrlUtil::bootloader();
            }
        });

    ModifierProcessor modifierProcessor(keyHandler);

    modifierProcessor.modifierSet()[0] = Modifier("Gm0", KeyId::Layer(3));
    modifierProcessor.modifierSet()[1] = Modifier("Gm1", KeyId::Layer(4));
    modifierProcessor.modifierSet()[2] = Modifier("Gm2", KeyId::Layer(5));
    
    modifierProcessor.modifierSet()[5] = Modifier("LShft", 0xe1);
    modifierProcessor.modifierSet()[6] = Modifier("RShft", 0xe5);

    MacroProcessor macroProcessor;
    
    UI::Home home(surface,
                  modifierProcessor.modifierSet());
    
    while (1)
    {
        keyHandler.poll(eventQueue);
        
        if (!eventQueue.empty())
        {
            auto event(eventQueue.pop());

            const auto& keyId(event.keyId);

            if (keyId.type() == KeyId::Type::kLayer)
            {
                keyHandler.setLayer(keyId.value(), event.pressed, eventQueue);
            }
            else
            {
                actionProcessor.processEvent(event, eventQueue);
                macroProcessor.processEvent(event, eventQueue);
            }
            
            if (modifierProcessor.processEvent(event, eventQueue))
            {
                home.update();
            }

            if (keyId.type() == KeyId::Type::kKey)
            {
                usbKeyboard.processKey(keyId.value(), event.pressed);
            }
        }
        
        home.paint();
    }
}
