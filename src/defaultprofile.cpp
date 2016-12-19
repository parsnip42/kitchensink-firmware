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
    
    keyboardState.lockSet[kLCtrl]  = Lock("LCtrl",  LCtrl);
    keyboardState.lockSet[kLShift] = Lock("LShift", LShift);
    keyboardState.lockSet[kLAlt]   = Lock("LAlt",   LAlt);
    keyboardState.lockSet[kLGui]   = Lock("LGui",   LGui);
    keyboardState.lockSet[kRCtrl]  = Lock("RCtrl",  RCtrl);
    keyboardState.lockSet[kRShift] = Lock("RShift", RShift);
    keyboardState.lockSet[kRAlt]   = Lock("RAlt",   RAlt);
    keyboardState.lockSet[kRGui]   = Lock("RGui",   RGui);

    keyboardState.lockSet[8]  = Lock("Gm0", KeyId::Layer(3));
    keyboardState.lockSet[11] = Lock("KSP", KeyId::Layer(4));

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

    layerStack[0].name = "Default";
    layerStack[0].mapping = { {
            { Grave, NonUsHash, K1, K2, K3, K4, K5, NonUsBackslash, KeyId::Lock(KeyId::LockType::kToggle, 8), KeyId::Lock(KeyId::LockType::kToggle, 9),
              F1, F2, 0, K6, K7, K8, K9, K0, Minus, Equal },
                
            { Esc, KeyId::Macro(KeyId::MacroType::kInvert, 10), Q, W, E, R, T, Tab, KeyId::Lock(KeyId::LockType::kToggle, 11),0,
              F3, F4, Backspace, Y, U, I, O, P, LBrace, RBrace },
            
            { 0, KeyId::Layer(2), A, S, D, F, G, 0, 0, 0,
              KeyId::Macro(KeyId::MacroType::kSync, 9), KeyId::Action(KeyId::ActionType::kBuiltIn, 2), 0, H, J, K, L, Semicolon, Enter },
            
            { 0, KeyId::Lock(KeyId::LockType::kTripleLock, kLShift), Z, X, C, V, B, Delete, 0, 0,
              KeyId::Action(KeyId::ActionType::kBuiltIn, 0),KeyId::Action(KeyId::ActionType::kMenu, 0), Quote, N, M, Comma, Dot, Slash, KeyId::Lock(kRShift) },
            
            { 0, KeyId::Lock(kLGui), KeyId::Lock(kRAlt), 0, 0, 0, KeyId::Lock(kLCtrl),KeyId::Layer(1),KeyId::Lock(kLAlt),0,
              0, KeyId::Lock(kLAlt), Space, KeyId::Lock(kRCtrl), End, Left, Up, Down, Right }
        } };
    
    layerStack[1].name = "Navigation";
    layerStack[1].mapping = { {
            { },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
              0, 0, Backspace, PageUp, End, Up, 0, 0, 0 },
            { 0, 0, 0, KeyId::Macro(KeyId::MacroType::kInvert, 0), KeyId::Macro(KeyId::MacroType::kInvert, 1), KeyId::Macro(KeyId::MacroType::kInvert, 2), KeyId::Macro(KeyId::MacroType::kInvert, 3), 0, 0, 0,
              0, 0, 0, Home, Left, Down, Right, 0, 0, 0 },
            { 0, 0, 0, LBrace, RBrace, KeyId::Macro(KeyId::MacroType::kInvert, 4), KeyId::Macro(KeyId::MacroType::kInvert, 5), 0, 0, 0,
              0, 0, 0, PageDown, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
              0, 0, KeyId::Macro(KeyId::MacroType::kInvert, 6), 0, 0, 0, 0, 0, 0, 0 }
        } };

    layerStack[2].name = "Number";
    layerStack[2].mapping = { {
            { },
            
            { 0, 0, F1, F2, F3, F4, F5, 0, 0, 0,
              0, 0, 0, 0, K7, K8, K9, 0, 0, 0 },
            
            { 0, 0, F6, F7, F8, F9, F10, 0, 0, 0,
              0, 0, 0, 0, K4, K5, K6, 0, 0, 0 },
            
            { 0, 0, F11, F12, F13, F14, F15, 0, 0, 0,
              0, 0, 0, 0, K1, K2, K3, 0, 0, 0 },
            
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
              0, 0, 0, 0, K0, 0, 0, 0, 0, 0 }
        } };

    layerStack[3].name = "Game";
    layerStack[3].mapping = { {
            { },
            { Esc, 0, Q, W, E, R, T, Tab, 0, 0,        /**/  F3, F4, Backspace, Y, U, I, O, P, LBrace, RBrace },
            { 0, Tab, A, S, D, F, G, 0, 0, 0,          /**/  F6, F5, 0, H, J, K, L, Semicolon, Enter },
            { 0, LShift, Z, X, C, V, B, 0, 0, 0,       /**/  F7, F8, Delete, N, M, Comma, Dot, Slash, RShift },
            { 0, 0, 0, 0, 0, 0, LCtrl, Space, LAlt, 0, /**/  0, LAlt, Space, RCtrl, End, Left, Up, Down, Right }
        } };

    layerStack[4].name = "Kerbal Space Program";
    layerStack[4].mapping = { {
            { KeyId::Macro(KeyId::MacroType::kInvert, 15),KeyId::Macro(KeyId::MacroType::kInvert, 16), K1, K2, K3, K4, K5, U, 0, 0,
              F1, F2, 0, K6, K7, K8, K9, K0, Minus, Equal },
            
            { Comma, Dot, G, Q, W, E, Insert, Space, 0, 0,
              F3, F4, Backspace, Y, U, I, O, P, LBrace, RBrace },
            
            { 0, M, KpDot, A, S, D, Delete, 0, 0, KeyId::Macro(KeyId::MacroType::kInvert, 18),
              KeyId::Macro(KeyId::MacroType::kInvert, 19), 0, 0, H, J, K, L, Semicolon, Enter },
            
            { 0, T, Z, X, C, V, B, KeyId::Macro(KeyId::MacroType::kInvert, 17), Esc, F5,
              F9, 0, Quote, N, M, Comma, Dot, Slash, KeyId::Lock(6) },
            
            { 0, R, 0, 0, 0, LAlt, LShift, LCtrl, X, 0,
              0, LAlt, Space, RCtrl, End, Left, Up, Down, Right }
        } };

}

}
