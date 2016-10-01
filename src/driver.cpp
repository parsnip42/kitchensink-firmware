#include "SdFat.h"

#include "actions.h"
#include "actioncontext.h"
#include "actionmanager.h"
#include "display.h"
#include "keymatrix.h"
#include "keymap.h"
#include "keymatrixevent.h"
#include "keymatrixeventdispatcher.h"
#include "layer.h"
#include "layerstack.h"
#include "tapping.h"
#include "usbkeyboard.h"

const KeyId layer0_[5][20]={
    { KEY_TILDE,KEY_NON_US_BS,KEY_1,KEY_2,KEY_3,KEY_4,KEY_5,KEY_NON_US_NUM,KeyId::Action(3),0,
      KEY_F1,KEY_F2,KEY_QUOTE,KEY_6,KEY_7,KEY_8,KEY_9,KEY_0,KEY_MINUS,KEY_EQUAL },

    { KEY_ESC,KeyId::Action(4),KEY_Q,KEY_W,KEY_E,KEY_R,KEY_T,KEY_TAB,0,0,
      KEY_F3,KEY_F4,KEY_BACKSPACE,KEY_Y,KEY_U,KEY_I,KEY_O,KEY_P,KEY_LEFT_BRACE,KEY_RIGHT_BRACE },
    
    {0,KeyId::Action(1),KEY_A,KEY_S,KEY_D,KEY_F,KEY_G,0,0,0,
     KEY_F6,KEY_F5, 0,KEY_H,KEY_J,KEY_K,KEY_L,KEY_SEMICOLON,KEY_ENTER },
    
    {0,MODIFIERKEY_LEFT_SHIFT,KEY_Z,KEY_X,KEY_C,KEY_V,KEY_B,0,0,KeyId::Action(2),
     KEY_F7,KEY_F8,KEY_DELETE,KEY_N,KEY_M,KEY_COMMA,KEY_PERIOD,KEY_SLASH,MODIFIERKEY_RIGHT_SHIFT },
    
     {0,MODIFIERKEY_LEFT_GUI,0,0,0,MODIFIERKEY_LEFT_SHIFT<<16|KEY_UP,MODIFIERKEY_LEFT_CTRL,KeyId::Action(0),MODIFIERKEY_LEFT_ALT,0,
     0,MODIFIERKEY_LEFT_ALT,KEY_SPACE,MODIFIERKEY_RIGHT_CTRL,KEY_END,KEY_LEFT,KEY_UP,KEY_DOWN,KEY_RIGHT }
};

const Layer layer0(layer0_);

const KeyId layer1_[5][20]={
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, KEY_BACKSPACE, KEY_PAGE_UP, KEY_END, KEY_UP, 0, 0, 0 },
    
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, KEY_HOME, KEY_LEFT,KEY_DOWN,KEY_RIGHT, 0, 0, 0 },

    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, KEY_PAGE_DOWN, 0, 0, 0, 0, 0, 0 },

    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, MODIFIERKEY_RIGHT_CTRL, 0, 0, 0, 0, 0, 0 },
};

const Layer layer1(layer1_);

const KeyId layer2_[5][20]={
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },

    { 0, 0, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, 0, 0, 0,
      0, 0, 0, 0, KEY_7, KEY_8, KEY_9, 0, 0, 0 },
    
    { 0, 0, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, 0, 0, 0,
      0, 0, 0, 0, KEY_4, KEY_5, KEY_6, 0, 0, 0 },
    
    { 0, 0, KEY_F11, KEY_F12, KEY_F13, KEY_F14, KEY_F15, 0, 0, 0,
      0, 0, 0, 0, KEY_1, KEY_2, KEY_3, 0, 0, 0 },
    
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, KEY_0, 0, 0, 0, 0, 0 }
};

const Layer layer2(layer2_);

const KeyId layer3_[5][20]={
    { KEY_TILDE,KEY_NON_US_BS,KEY_1,KEY_2,KEY_3,KEY_4,KEY_5,KEY_NON_US_NUM,KeyId::Action(3),0,
      KEY_F1,KEY_F2,KEY_QUOTE,KEY_6,KEY_7,KEY_8,KEY_9,KEY_0,KEY_MINUS,KEY_EQUAL },

    { KEY_ESC,MODIFIERKEY_LEFT_SHIFT<<16|KEY_MINUS,KEY_Q,KEY_W,KEY_E,KEY_R,KEY_T,KEY_TAB,0,0,
      KEY_F3,KEY_F4,KEY_BACKSPACE,KEY_Y,KEY_U,KEY_I,KEY_O,KEY_P,KEY_LEFT_BRACE,KEY_RIGHT_BRACE },
    
    {0,KEY_TAB,KEY_A,KEY_S,KEY_D,KEY_F,KEY_G,0,0,0,
     KEY_F6,KEY_F5,0,KEY_H,KEY_J,KEY_K,KEY_L,KEY_SEMICOLON,KEY_ENTER },
    
    {0,MODIFIERKEY_LEFT_SHIFT,KEY_Z,KEY_X,KEY_C,KEY_V,KEY_B,0,0,0,
     KEY_F7,KEY_F8,KEY_DELETE,KEY_N,KEY_M,KEY_COMMA,KEY_PERIOD,KEY_SLASH,MODIFIERKEY_RIGHT_SHIFT },
    
     {0,MODIFIERKEY_LEFT_GUI,0,0,0,MODIFIERKEY_LEFT_SHIFT<<16|KEY_UP,MODIFIERKEY_LEFT_CTRL,KEY_SPACE,MODIFIERKEY_LEFT_ALT,0,
     0,MODIFIERKEY_LEFT_ALT,KEY_SPACE,MODIFIERKEY_RIGHT_CTRL,KEY_END,KEY_LEFT,KEY_UP,KEY_DOWN,KEY_RIGHT }
};

const Layer layer3(layer3_);

SdFat sd;

void setup() {
    KeyMatrix::init();
}

void loop() {
    Display display;

    display.init();

    display.paint(30, 0, "Start");
    
    KeyMatrix matrixA(0x20, 0x7C00, 0x3FF);
    KeyMatrix matrixB(0x21, 0x3E00, 0xC0FF);
    
    display.paint(30, 14, "Config");

    if (!sd.begin(10, SPI_HALF_SPEED)) {
        if (sd.card()->errorCode()) {
            char sderr[48];
            sprintf(sderr,"SD Failed : 0x%x", sd.card()->errorCode());
            display.paint(30, 28, sderr);
        }
    }
    else
    {
        char sdinfo[48];
        sprintf(sdinfo, "SD OK : %dMB / FAT%d", (int)(0.000512 * sd.card()->cardSize() + 0.5), sd.vol()->fatType());
        display.paint(30, 28, sdinfo);

        SdBaseFile myFile;

        if (!myFile.open("test.cfg", O_READ)) {
            display.paint(30, 42, "Couldn't open file");
        }
        else
        {
            char data[48];

            myFile.fgets(data, sizeof(data));
            
            display.paint(30, 42, data);

            myFile.close();
        }
    }

    
    char outStr[48];

    bool displayDebug = true;

    LayerStack layerStack;

    layerStack.assignLayer(&layer0, 0);
    layerStack.assignLayer(&layer1, 1);
    layerStack.assignLayer(&layer2, 2);
    layerStack.assignLayer(&layer3, 3);
    layerStack.setLayer(0, true);


    UsbKeyboard usbKeyboard;
    ActionManager actionManager;

    actionManager.registerAction(0, Actions::layerModifier(layerStack, 1));
    actionManager.registerAction(1, Actions::layerModifier(layerStack, 2));
    actionManager.registerAction(3, Actions::toggleLayer(layerStack, 3));
    actionManager.registerAction(4, Actions::modifierKey(usbKeyboard, MODIFIERKEY_LEFT_SHIFT, KEY_MINUS));

    actionManager.registerAction(
        2,
        [&display, &displayDebug](const ActionContext& context)
        {
            if (context.state == KeyState::kPressed && context.taps == 2)
            {
                displayDebug = !displayDebug;
                
                if (!displayDebug)
                {
                    display.clear();
                }
            }
        });


    KeyMatrixEventDispatcher dispatcherA({4,3,2,1,0}, {0,1,2,3,4,5,6,7,9,8,10,11,12,13,14,15});
    KeyMatrixEventDispatcher dispatcherB({0,1,2,3,4}, {12,13,14,15,16,17,18,19,20,21,22,23,24,25,11,10});        

    Tapping tapping(500);
        
    auto callback([&](const KeyMatrixEvent& event)
    {
        KeyId keyId(layerStack.at(event.row, event.column));

        if (event.state == KeyState::kPressed)
        {
            tapping.processKey(keyId);
        }
        
        if (keyId.type() == KeyId::kModifier)
        {
            if (event.state != KeyState::kReleased)
            {
                usbKeyboard.setModifier(keyId.value());
            }

            if (event.state != KeyState::kHeld)
            {
                usbKeyboard.markDirty();
            }
        }
        else if (keyId.type() == KeyId::kKey)
        {
            if (event.state != KeyState::kReleased)
            {
                usbKeyboard.setKey(keyId.value());
            }
                              
            if (event.state != KeyState::kHeld)
            {
                usbKeyboard.markDirty();
            }
        }
        else if (keyId.type() == KeyId::kAction)
        {
            actionManager.fireAction(keyId.value(),
                                     ActionContext(event.state,
                                                   tapping.count(keyId)));
        }
    });
        
    while (1)
    {
        if (!matrixA.scan() && !matrixB.scan())
        {
            continue;
        }
        
        dispatcherA.dispatch(matrixA, callback);
        dispatcherB.dispatch(matrixB, callback);

        if (displayDebug) 
        {
            sprintf(outStr,"|%4.4x%4.4x%4.4x%4.4x%4.4x|",
                    (int)matrixA[0].data(),
                    (int)matrixA[1].data(),
                    (int)matrixA[2].data(),
                    (int)matrixA[3].data(),
                    (int)matrixA[4].data());
            display.paint(48, 0, outStr);
            
            sprintf(outStr,"|%4.4x%4.4x%4.4x%4.4x%4.4x|",
                    (int)matrixB[0].data(),
                    (int)matrixB[1].data(),
                    (int)matrixB[2].data(),
                    (int)matrixB[3].data(),
                    (int)matrixB[4].data());
            display.paint(48, 14, outStr);
        }

        usbKeyboard.update();
    }
}
