#include "defaultprofile.h"

#include "keyid.h"
#include "keyboardstate.h"
#include "keycodes.h"

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
    using namespace KeyCodes;
    
    keyboardState.modifierSet[kLCtrl]  = Modifier("LCtrl",  LCtrl);
    keyboardState.modifierSet[kLShift] = Modifier("LShift", LShift);
    keyboardState.modifierSet[kLAlt]   = Modifier("LAlt",   LAlt);
    keyboardState.modifierSet[kLGui]   = Modifier("LGui",   LGui);
    keyboardState.modifierSet[kRCtrl]  = Modifier("RCtrl",  RCtrl);
    keyboardState.modifierSet[kRShift] = Modifier("RShift", RShift);
    keyboardState.modifierSet[kRAlt]   = Modifier("RAlt",   RAlt);
    keyboardState.modifierSet[kRGui]   = Modifier("RGui",   RGui);

    keyboardState.modifierSet[8]  = Modifier("Gm0", KeyId::Layer(3));
    keyboardState.modifierSet[11] = Modifier("KSP", KeyId::Layer(4));

    keyboardState.macroSet.setMacro(0, {
            KeyEvent(KeyId(LBrace)),
            KeyEvent(KeyId(LShift)),
            });

    keyboardState.macroSet.setMacro(1, {
            KeyEvent(KeyId(RBrace)),
            KeyEvent(KeyId(LShift)),
            });

    keyboardState.macroSet.setMacro(2, {
            KeyEvent(KeyId(K9)),
            KeyEvent(KeyId(LShift)),
            });

    keyboardState.macroSet.setMacro(3, {
            KeyEvent(KeyId(K0)),
            KeyEvent(KeyId(LShift)),
            });

    keyboardState.macroSet.setMacro(4, {
            KeyEvent(KeyId(Comma)),
            KeyEvent(KeyId(LShift)),
            });

    keyboardState.macroSet.setMacro(5, {
            KeyEvent(KeyId(Dot)),
            KeyEvent(KeyId(LShift)),
            });
    
    keyboardState.macroSet.setMacro(6, {
            KeyEvent(KeyId(Space)),
            KeyEvent(KeyId(LCtrl)),
            });

    keyboardState.macroSet.setMacro(10, {
            KeyEvent(KeyId(Minus)),
            KeyEvent(KeyId(LShift)),
            });

    keyboardState.macroSet.setMacro(11, {
            KeyEvent(KeyId(Minus)),
            KeyEvent(KeyId(LShift)),
            });

    keyboardState.macroSet.setMacro(15, {
            KeyEvent(KeyId(Comma)),
            KeyEvent(KeyId(LAlt)),
            });
    keyboardState.macroSet.setMacro(16, {
            KeyEvent(KeyId(Dot)),
            KeyEvent(KeyId(LAlt)),
            });
    keyboardState.macroSet.setMacro(17, {
            KeyEvent(KeyId(L)),
            KeyEvent(KeyId(LAlt)),
            });    
    keyboardState.macroSet.setMacro(18, {
            KeyEvent(KeyId(F5)),
            KeyEvent(KeyId(LAlt)),
            });
    keyboardState.macroSet.setMacro(19, {
            KeyEvent(KeyId(F9)),
            KeyEvent(KeyId(LAlt)),
            });

    auto& layerStack(keyboardState.layerStack);
    
    layerStack.setLayer(0, true);

    layerStack.assignLayer(0, Layer("Default", {
                { Grave, NonUsHash, K1, K2, K3, K4, K5, NonUsBackslash, KeyId::Modifier(KeyId::ModifierType::kToggle, 8), KeyId::Modifier(KeyId::ModifierType::kToggle, 9),
                    F1, F2, 0, K6, K7, K8, K9, K0, Minus, Equal },
                
                { Esc, KeyId::Macro(KeyId::MacroType::kInvert, 10), Q, W, E, R, T, Tab, KeyId::Modifier(KeyId::ModifierType::kToggle, 11),0,
                    F3, F4, Backspace, Y, U, I, O, P, LBrace, RBrace },
                
                { 0, KeyId::Layer(2), A, S, D, F, G, 0, KeyId::Macro(KeyId::MacroType::kSync, 9), 0,
                    0, KeyId::Action(KeyId::ActionType::kBuiltIn, 2), 0, H, J, K, L, Semicolon, Enter },
                
                { 0, KeyId::Modifier(KeyId::ModifierType::kTripleLock, kLShift), Z, X, C, V, B, Delete, 0, 0,
                    KeyId::Action(KeyId::ActionType::kBuiltIn, 0),KeyId::Action(KeyId::ActionType::kMenu, 0), Quote, N, M, Comma, Dot, Slash, KeyId::Modifier(kRShift) },
                
                { 0, KeyId::Modifier(kLGui), KeyId::Modifier(kRAlt), 0, 0, 0, KeyId::Modifier(kLCtrl),KeyId::Layer(1),KeyId::Modifier(kLAlt),0,
                    0, KeyId::Modifier(kLAlt), Space, KeyId::Modifier(kRCtrl), End, Left, Up, Down, Right }
            }));

    layerStack.assignLayer(1, Layer("Navigation", {
                { },
                
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0, Backspace, PageUp, End, Up, 0, 0, 0 },
                
                { 0, 0, 0, KeyId::Macro(KeyId::MacroType::kInvert, 0), KeyId::Macro(KeyId::MacroType::kInvert, 1), KeyId::Macro(KeyId::MacroType::kInvert, 2), KeyId::Macro(KeyId::MacroType::kInvert, 3), 0, 0, 0,
                    0, 0, 0, Home, Left, Down, Right, 0, 0, 0 },
                
                { 0, 0, 0, LBrace, RBrace, KeyId::Macro(KeyId::MacroType::kInvert, 4), KeyId::Macro(KeyId::MacroType::kInvert, 5), 0, 0, 0,
                    0, 0, 0, PageDown, 0, 0, 0, 0, 0, 0 },
                
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0, KeyId::Macro(KeyId::MacroType::kInvert, 6), 0, 0, 0, 0, 0, 0, 0 }
            }));
    
    layerStack.assignLayer(2, Layer("Number", {
                { },
                
                { 0, 0, F1, F2, F3, F4, F5, 0, 0, 0,
                    0, 0, 0, 0, K7, K8, K9, 0, 0, 0 },
                
                { 0, 0, F6, F7, F8, F9, F10, 0, 0, 0,
                    0, 0, 0, 0, K4, K5, K6, 0, 0, 0 },
                
                { 0, 0, F11, F12, F13, F14, F15, 0, 0, 0,
                    0, 0, 0, 0, K1, K2, K3, 0, 0, 0 },
                
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, K0, 0, 0, 0, 0, 0 }
            }));
    
    layerStack.assignLayer(3, Layer("Game", {
                { },
                { Esc, 0, Q, W, E, R, T, Tab, 0, 0,        /**/  F3, F4, Backspace, Y, U, I, O, P, LBrace, RBrace },
                { 0, Tab, A, S, D, F, G, 0, 0, 0,          /**/  F6, F5, 0, H, J, K, L, Semicolon, Enter },
                { 0, LShift, Z, X, C, V, B, 0, 0, 0,       /**/  F7, F8, Delete, N, M, Comma, Dot, Slash, RShift },
                { 0, 0, 0, 0, 0, 0, LCtrl, Space, LAlt, 0, /**/  0, LAlt, Space, RCtrl, End, Left, Up, Down, Right }
            }));


    layerStack.assignLayer(4, Layer("Kerbal Space Program", {
                { KeyId::Macro(KeyId::MacroType::kInvert, 15),KeyId::Macro(KeyId::MacroType::kInvert, 16), K1, K2, K3, K4, K5, U, 0, 0,
                    F1, F2, 0, K6, K7, K8, K9, K0, Minus, Equal },
                
                { Comma, Dot, G, Q, W, E, Insert, Space, 0, 0,
                    F3, F4, Backspace, Y, U, I, O, P, LBrace, RBrace },
                
                { 0, M, KpDot, A, S, D, Delete, 0, 0, KeyId::Macro(KeyId::MacroType::kInvert, 18),
                    KeyId::Macro(KeyId::MacroType::kInvert, 19), 0, 0, H, J, K, L, Semicolon, Enter },
                
                { 0, T, Z, X, C, V, B, KeyId::Macro(KeyId::MacroType::kInvert, 17), Esc, F5,
                    F9, 0, Quote, N, M, Comma, Dot, Slash, KeyId::Modifier(6) },
                
                { 0, R, 0, 0, 0, LAlt, LShift, LCtrl, X, 0,
                    0, LAlt, Space, RCtrl, End, Left, Up, Down, Right }
            }));

}

}
