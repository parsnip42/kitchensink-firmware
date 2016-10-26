#include "defaultlayers.h"

#include "keyhandler.h"
#include "keyid.h"
#include "modifierid.h"

#include <keylayouts.h>

#define KEY_LCTRL  0xe0
#define KEY_LSHIFT 0xe1
#define KEY_LALT   0xe2
#define KEY_LGUI   0xe3
#define KEY_RCTRL  0xe4
#define KEY_RSHIFT 0xe5
#define KEY_RALT   0xe6
#define KEY_RGUI   0xe7

namespace DefaultLayers
{

void init(KeyHandler& keyHandler)
{
    keyHandler.assignLayer(0, Layer({
                { KEY_TILDE,KEY_NON_US_NUM,KEY_1,KEY_2,KEY_3,KEY_4,KEY_5,KEY_NON_US_BS,KeyId::Modifier(KeyId::ModifierType::kToggle, 0),KeyId::Modifier(KeyId::ModifierType::kToggle, 1),
                    KEY_F1,KEY_F2,0,KEY_6,KEY_7,KEY_8,KEY_9,KEY_0,KEY_MINUS,KEY_EQUAL },
                
                { KEY_ESC,KeyId::Multi(10),KEY_Q,KEY_W,KEY_E,KEY_R,KEY_T,KEY_TAB,0,0,
                    KEY_F3,KEY_F4,KEY_BACKSPACE,KEY_Y,KEY_U,KEY_I,KEY_O,KEY_P,KEY_LEFT_BRACE,KEY_RIGHT_BRACE },
                
                {0,KeyId::Layer(2),KEY_A,KEY_S,KEY_D,KEY_F,KEY_G,0,0,0,
                    KEY_F6,KEY_F5, 0,KEY_H,KEY_J,KEY_K,KEY_L,KEY_SEMICOLON,KEY_ENTER },
                
                {0,KEY_LSHIFT,KEY_Z,KEY_X,KEY_C,KEY_V,KEY_B,KEY_DELETE,KeyId::Action(5),KeyId::Action(2),
                    KeyId::Action(9),0,KEY_QUOTE,KEY_N,KEY_M,KEY_COMMA,KEY_PERIOD,KEY_SLASH,KEY_RSHIFT },
                
                {0,KEY_LGUI,0,0,0,0,KEY_LCTRL,KeyId::Layer(1),KEY_LALT,0,
                    0,KEY_LALT,KEY_SPACE,KEY_RCTRL,KEY_END,KEY_LEFT,KEY_UP,KEY_DOWN,KEY_RIGHT }
            }));

    keyHandler.assignLayer(1, Layer({
                { },
                
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0, KEY_BACKSPACE, KEY_PAGE_UP, KEY_END, KEY_UP, 0, 0, 0 },
                
                { 0, 0, 0, KeyId::Multi(0), KeyId::Multi(1), KeyId::Multi(2), KeyId::Multi(3), 0, 0, 0,
                    0, 0, 0, KEY_HOME, KEY_LEFT,KEY_DOWN,KEY_RIGHT, 0, 0, 0 },
                
                { 0, 0, 0, KEY_LEFT_BRACE, KEY_RIGHT_BRACE, KeyId::Multi(4), KeyId::Multi(5), 0, 0, 0,
                    0, 0, 0, KEY_PAGE_DOWN, 0, 0, 0, 0, 0, 0 },
                
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0, KeyId::Multi(11), 0, 0, 0, 0, 0, 0, 0 }
            }));
    
    keyHandler.assignLayer(2, Layer({
                { },
                
                { 0, 0, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, 0, 0, 0,
                    0, 0, 0, 0, KEY_7, KEY_8, KEY_9, 0, 0, 0 },
                
                { 0, 0, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, 0, 0, 0,
                    0, 0, 0, 0, KEY_4, KEY_5, KEY_6, 0, 0, 0 },
                
                { 0, 0, KEY_F11, KEY_F12, KEY_F13, KEY_F14, KEY_F15, 0, 0, 0,
                    0, 0, 0, 0, KEY_1, KEY_2, KEY_3, 0, 0, 0 },
                
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, KEY_0, 0, 0, 0, 0, 0 }
            }));
    
    keyHandler.assignLayer(3, Layer({
                { },
                
                { KEY_ESC,0,KEY_Q,KEY_W,KEY_E,KEY_R,KEY_T,KEY_TAB,0,0,
                    KEY_F3,KEY_F4,KEY_BACKSPACE,KEY_Y,KEY_U,KEY_I,KEY_O,KEY_P,KEY_LEFT_BRACE,KEY_RIGHT_BRACE },
                
                {0,KEY_TAB,KEY_A,KEY_S,KEY_D,KEY_F,KEY_G,0,0,0,
                    KEY_F6,KEY_F5,0,KEY_H,KEY_J,KEY_K,KEY_L,KEY_SEMICOLON,KEY_ENTER },
                
                {0,KEY_LSHIFT,KEY_Z,KEY_X,KEY_C,KEY_V,KEY_B,0,0,0,
                    KEY_F7,KEY_F8,KEY_DELETE,KEY_N,KEY_M,KEY_COMMA,KEY_PERIOD,KEY_SLASH,KEY_RSHIFT },
                
                {0,KEY_LGUI,0,0,0,0,KEY_LCTRL,KEY_SPACE,KEY_LALT,0,
                    0,KEY_LALT,KEY_SPACE,KEY_RCTRL,KEY_END,KEY_LEFT,KEY_UP,KEY_DOWN,KEY_RIGHT }
            }));


    keyHandler.assignLayer(4, Layer({
                { },
                
                { KEY_ESC,0,KEY_Q,KEY_W,KEY_E,KEY_R,KEY_T,KEY_TAB,0,0,
                    0,0,KEY_BACKSPACE,KEY_Y,KEY_U,KEY_I,KEY_O,KEY_P,KEY_LEFT_BRACE,KEY_RIGHT_BRACE },
                
                {0,KeyId::Modifier(KeyId::ModifierType::kToggle, 2),KEY_A,KEY_S,KEY_D,KEY_F,KEY_G,0,0,0,
                    0,0,0,KEY_H,KEY_J,KEY_K,KEY_L,KEY_SEMICOLON,KEY_ENTER },
                
                {0,KEY_LSHIFT,KEY_Z,KEY_X,KEY_C,KEY_V,KEY_B,0,0,0,
                    0,0,KEY_DELETE,KEY_N,KEY_M,KEY_COMMA,KEY_PERIOD,KEY_SLASH,KEY_RSHIFT },
                
                {0,KEY_LGUI,0,0,0,0,KEY_LCTRL,KEY_SPACE,KEY_LALT,0,
                    0,KEY_LALT,KEY_SPACE,KEY_RCTRL,KEY_END,KEY_LEFT,KEY_UP,KEY_DOWN,KEY_RIGHT }
            }));

        keyHandler.assignLayer(5, Layer({
                { },
                
                { KEY_ESC,0,0,0,KEY_UP,0,0,KEY_TAB,0,0,
                    0,0,KEY_BACKSPACE,KEY_Y,KEY_U,KEY_I,KEY_O,KEY_P,KEY_LEFT_BRACE,KEY_RIGHT_BRACE },
                
                {0,0,0,KEY_LEFT,KEY_DOWN,KEY_RIGHT,0,0,0,0,
                    0,0,0,KEY_H,KEY_J,KEY_K,KEY_L,KEY_SEMICOLON,KEY_ENTER },
                
                { },
                
                { }
            }));
}

}
