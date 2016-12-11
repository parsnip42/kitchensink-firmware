#include "defaultprofile.h"

#include "keyid.h"
#include "keyboardstate.h"

#include <keylayouts.h>

#define KEY_LCTRL  0xe0
#define KEY_LSHIFT 0xe1
#define KEY_LALT   0xe2
#define KEY_LGUI   0xe3
#define KEY_RCTRL  0xe4
#define KEY_RSHIFT 0xe5
#define KEY_RALT   0xe6
#define KEY_RGUI   0xe7

namespace DefaultProfile
{

namespace
{
constexpr int kLCtrl  = 0;
constexpr int kLShift = 1;
constexpr int kLAlt   = 2;
constexpr int kLGui   = 3;
constexpr int kRCtrl  = 4;
constexpr int kRShift = 5;
constexpr int kRAlt   = 6;
constexpr int kRGui   = 7;
}

void init(KeyboardState& keyboardState)
{
    keyboardState.modifierSet[kLCtrl]  = Modifier("LCtrl",  KEY_LCTRL);
    keyboardState.modifierSet[kLShift] = Modifier("LShift", KEY_LSHIFT);
    keyboardState.modifierSet[kLAlt]   = Modifier("LAlt",   KEY_LALT);
    keyboardState.modifierSet[kLGui]   = Modifier("LGui",   KEY_LGUI);
    keyboardState.modifierSet[kRCtrl]  = Modifier("RCtrl",  KEY_RCTRL);
    keyboardState.modifierSet[kRShift] = Modifier("RShift", KEY_RSHIFT);
    keyboardState.modifierSet[kRAlt]   = Modifier("RAlt",   KEY_RALT);
    keyboardState.modifierSet[kRGui]   = Modifier("RGui",   KEY_RGUI);

    keyboardState.modifierSet[8]  = Modifier("Gm0", KeyId::Layer(3));
    keyboardState.modifierSet[9]  = Modifier("Gm1", KeyId::Layer(4));
    keyboardState.modifierSet[10] = Modifier("Gm2", KeyId::Layer(5));
    keyboardState.modifierSet[11] = Modifier("KSP", KeyId::Layer(6));

    keyboardState.macroSet.setMacro(0, {
            KeyEvent(KeyId(KEY_LEFT_BRACE)),
            KeyEvent(KeyId(0xe1)),
            });

    keyboardState.macroSet.setMacro(1, {
            KeyEvent(KeyId(KEY_RIGHT_BRACE)),
            KeyEvent(KeyId(0xe1)),
            });

    keyboardState.macroSet.setMacro(2, {
            KeyEvent(KeyId(KEY_9)),
            KeyEvent(KeyId(0xe1)),
            });

    keyboardState.macroSet.setMacro(3, {
            KeyEvent(KeyId(KEY_0)),
            KeyEvent(KeyId(0xe1)),
            });

    keyboardState.macroSet.setMacro(4, {
            KeyEvent(KeyId(KEY_COMMA)),
            KeyEvent(KeyId(0xe1)),
            });

    keyboardState.macroSet.setMacro(5, {
            KeyEvent(KeyId(KEY_PERIOD)),
            KeyEvent(KeyId(0xe1)),
            });
    
    keyboardState.macroSet.setMacro(6, {
            KeyEvent(KeyId(KEY_SPACE)),
            KeyEvent(KeyId(0xe0)),
            });

    keyboardState.macroSet.setMacro(10, {
            KeyEvent(KeyId(KEY_MINUS)),
            KeyEvent(KeyId(0xe1)),
            });

    keyboardState.macroSet.setMacro(11, {
            KeyEvent(KeyId(KEY_MINUS)),
            KeyEvent(KeyId(0xe1)),
            });

    keyboardState.macroSet.setMacro(15, {
            KeyEvent(KeyId(KEY_COMMA)),
            KeyEvent(KeyId(0xe2)),
            });
    keyboardState.macroSet.setMacro(16, {
            KeyEvent(KeyId(KEY_PERIOD)),
            KeyEvent(KeyId(0xe2)),
            });
    keyboardState.macroSet.setMacro(17, {
            KeyEvent(KeyId(KEY_L)),
            KeyEvent(KeyId(0xe2)),
            });    
    keyboardState.macroSet.setMacro(18, {
            KeyEvent(KeyId(KEY_F5)),
            KeyEvent(KeyId(0xe2)),
            });
    keyboardState.macroSet.setMacro(19, {
            KeyEvent(KeyId(KEY_F9)),
            KeyEvent(KeyId(0xe2)),
            });

    auto& layerStack(keyboardState.layerStack);
    
    layerStack.setLayer(0, true);

    layerStack.assignLayer(0, Layer("Default \x7f", {
                { KEY_TILDE,KEY_NON_US_NUM,KEY_1,KEY_2,KEY_3,KEY_4,KEY_5,KEY_NON_US_BS,KeyId::Modifier(KeyId::ModifierType::kToggle, 8),KeyId::Modifier(KeyId::ModifierType::kToggle, 9),
                    KEY_F1,KEY_F2,0,KEY_6,KEY_7,KEY_8,KEY_9,KEY_0,KEY_MINUS,KEY_EQUAL },
                
                { KEY_ESC,KeyId::Macro(KeyId::MacroType::kInvert, 10),KEY_Q,KEY_W,KEY_E,KEY_R,KEY_T,KEY_TAB,KeyId::Modifier(KeyId::ModifierType::kToggle, 11),0,
                    KEY_F3,KEY_F4,KEY_BACKSPACE,KEY_Y,KEY_U,KEY_I,KEY_O,KEY_P,KEY_LEFT_BRACE,KEY_RIGHT_BRACE },
                
                {0,KeyId::Layer(2),KEY_A,KEY_S,KEY_D,KEY_F,KEY_G,0,KeyId::Macro(KeyId::MacroType::kSync, 9),0,
                    KEY_F6,KEY_F5, 0,KEY_H,KEY_J,KEY_K,KEY_L,KEY_SEMICOLON,KEY_ENTER },
                
                {0,KeyId::Modifier(kLShift),KEY_Z,KEY_X,KEY_C,KEY_V,KEY_B,KEY_DELETE,0,0,
                    KeyId::Action(KeyId::ActionType::kBuiltIn, 0),KeyId::Action(KeyId::ActionType::kMenu, 0),KEY_QUOTE,KEY_N,KEY_M,KEY_COMMA,KEY_PERIOD,KEY_SLASH,KeyId::Modifier(kRShift) },
                
                {0,KeyId::Modifier(kLGui),KeyId::Modifier(kRAlt),0,0,0,KeyId::Modifier(kLCtrl),KeyId::Layer(1),KeyId::Modifier(kLAlt),0,
                    0,KeyId::Modifier(kLAlt),KEY_SPACE,KeyId::Modifier(kRCtrl),KEY_END,KEY_LEFT,KEY_UP,KEY_DOWN,KEY_RIGHT }
            }));

    layerStack.assignLayer(1, Layer("Navigation", {
                { },
                
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0, KEY_BACKSPACE, KEY_PAGE_UP, KEY_END, KEY_UP, 0, 0, 0 },
                
                { 0, 0, 0, KeyId::Macro(KeyId::MacroType::kInvert, 0), KeyId::Macro(KeyId::MacroType::kInvert, 1), KeyId::Macro(KeyId::MacroType::kInvert, 2), KeyId::Macro(KeyId::MacroType::kInvert, 3), 0, 0, 0,
                    0, 0, 0, KEY_HOME, KEY_LEFT,KEY_DOWN,KEY_RIGHT, 0, 0, 0 },
                
                { 0, 0, 0, KEY_LEFT_BRACE, KEY_RIGHT_BRACE, KeyId::Macro(KeyId::MacroType::kInvert, 4), KeyId::Macro(KeyId::MacroType::kInvert, 5), 0, 0, 0,
                    0, 0, 0, KEY_PAGE_DOWN, 0, 0, 0, 0, 0, 0 },
                
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0, KeyId::Macro(KeyId::MacroType::kInvert, 6), 0, 0, 0, 0, 0, 0, 0 }
            }));
    
    layerStack.assignLayer(2, Layer("Number", {
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
    
    layerStack.assignLayer(3, Layer("Game 0", {
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


    layerStack.assignLayer(4, Layer("Game 1", {
                { },
                
                { KEY_ESC,0,KEY_Q,KEY_W,KEY_E,KEY_R,KEY_T,KEY_TAB,0,0,
                    0,0,KEY_BACKSPACE,KEY_Y,KEY_U,KEY_I,KEY_O,KEY_P,KEY_LEFT_BRACE,KEY_RIGHT_BRACE },
                
                {0,KeyId::Modifier(KeyId::ModifierType::kToggle, 10),KEY_A,KEY_S,KEY_D,KEY_F,KEY_G,0,0,0,
                    0,0,0,KEY_H,KEY_J,KEY_K,KEY_L,KEY_SEMICOLON,KEY_ENTER },
                
                {0,KEY_LSHIFT,KEY_Z,KEY_X,KEY_C,KEY_V,KEY_B,0,0,0,
                    0,0,KEY_DELETE,KEY_N,KEY_M,KEY_COMMA,KEY_PERIOD,KEY_SLASH,KEY_RSHIFT },
                
                {0,KEY_LGUI,0,0,0,0,KEY_LCTRL,KEY_SPACE,KEY_LALT,0,
                    0,KEY_LALT,KEY_SPACE,KEY_RCTRL,KEY_END,KEY_LEFT,KEY_UP,KEY_DOWN,KEY_RIGHT }
            }));

    layerStack.assignLayer(5, Layer("Game 2", {
                { },
                
                { KEY_ESC,0,0,0,KEY_UP,0,0,KEY_TAB,0,0,
                    0,0,KEY_BACKSPACE,KEY_Y,KEY_U,KEY_I,KEY_O,KEY_P,KEY_LEFT_BRACE,KEY_RIGHT_BRACE },
                
                {0,0,0,KEY_LEFT,KEY_DOWN,KEY_RIGHT,0,0,0,0,
                    0,0,0,KEY_H,KEY_J,KEY_K,KEY_L,KEY_SEMICOLON,KEY_ENTER },
                
                { },
                
                { }
            }));

    layerStack.assignLayer(6, Layer("Kerbal Space Program", {
                { KeyId::Macro(KeyId::MacroType::kInvert, 15),KeyId::Macro(KeyId::MacroType::kInvert, 16),KEY_1,KEY_2,KEY_3,KEY_4,KEY_5,KEY_U,0,0,
                    KEY_F1,KEY_F2,0,KEY_6,KEY_7,KEY_8,KEY_9,KEY_0,KEY_MINUS,KEY_EQUAL },
                
                { KEY_COMMA,KEY_PERIOD,KEY_G,KEY_Q,KEY_W,KEY_E,KEY_INSERT,KEY_SPACE,0,0,
                    KEY_F3,KEY_F4,KEY_BACKSPACE,KEY_Y,KEY_U,KEY_I,KEY_O,KEY_P,KEY_LEFT_BRACE,KEY_RIGHT_BRACE },
                
                {0,KEY_M,KEYPAD_PERIOD,KEY_A,KEY_S,KEY_D,KEY_DELETE,0,0,KeyId::Macro(KeyId::MacroType::kInvert, 18),
                    KeyId::Macro(KeyId::MacroType::kInvert, 19),0,0,KEY_H,KEY_J,KEY_K,KEY_L,KEY_SEMICOLON,KEY_ENTER },
                
                {0,KEY_T,KEY_Z,KEY_X,KEY_C,KEY_V,KEY_B,KeyId::Macro(KeyId::MacroType::kInvert, 17),KEY_ESC,KEY_F5,
                    KEY_F9,0,KEY_QUOTE,KEY_N,KEY_M,KEY_COMMA,KEY_PERIOD,KEY_SLASH,KeyId::Modifier(6) },
                
                {0,KEY_R,0,0,0,KEY_LALT,KEY_LSHIFT,KEY_LCTRL,KEY_X,0,
                    0,KEY_LALT,KEY_SPACE,KEY_RCTRL,KEY_END,KEY_LEFT,KEY_UP,KEY_DOWN,KEY_RIGHT }
            }));

}

}
