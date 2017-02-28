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

namespace
{
constexpr KeyId Macro(int macroId)
{
    return KeyId::Macro(macroId);
}

constexpr KeyId EditMacro(int macroId)
{
    return KeyId::Action(KeyId::ActionType::kEditMacro, macroId);
}
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

    keyboardState.macroSet.setMacro(0, MacroType::kInvert, "{", {
            KeyEvent(KeyId(LShift)),
            KeyEvent(KeyId(LBrace)),
            });

    keyboardState.macroSet.setMacro(1, MacroType::kInvert, "{",{
            KeyEvent(KeyId(LShift)),
            KeyEvent(KeyId(RBrace)),
            });

    keyboardState.macroSet.setMacro(2, MacroType::kInvert, "(",{
            KeyEvent(KeyId(LShift)),
            KeyEvent(KeyId(K9)),
            });

    keyboardState.macroSet.setMacro(3, MacroType::kInvert, ")",{
            KeyEvent(KeyId(LShift)),
            KeyEvent(KeyId(K0)),
            });

    keyboardState.macroSet.setMacro(4, MacroType::kInvert, {
            KeyEvent(KeyId(LShift)),
            KeyEvent(KeyId(Comma)),
            });

    keyboardState.macroSet.setMacro(5, MacroType::kInvert, {
            KeyEvent(KeyId(LShift)),
            KeyEvent(KeyId(Dot)),
            });
    
    keyboardState.macroSet.setMacro(6, MacroType::kInvert, {
            KeyEvent(KeyId(LCtrl)),
            KeyEvent(KeyId(Space)),
            });

    keyboardState.macroSet.setMacro(10, MacroType::kInvert, {
            KeyEvent(KeyId(LShift)),
            KeyEvent(KeyId(Minus)),
            });

    keyboardState.macroSet.setMacro(11, MacroType::kInvert, {
            KeyEvent(KeyId(LShift)),
            KeyEvent(KeyId(Minus)),
            });

    keyboardState.macroSet.setMacro(15, MacroType::kInvert, {
            KeyEvent(KeyId(LAlt)),
            KeyEvent(KeyId(Comma)),
            });
    
    keyboardState.macroSet.setMacro(16, MacroType::kInvert, {
            KeyEvent(KeyId(LAlt)),
            KeyEvent(KeyId(Dot)),
            });
    
    keyboardState.macroSet.setMacro(17, MacroType::kInvert, {
            KeyEvent(KeyId(LAlt)),
            KeyEvent(KeyId(L)),
            });
    
    keyboardState.macroSet.setMacro(18, MacroType::kInvert, {
            KeyEvent(KeyId(LAlt)),
            KeyEvent(KeyId(F5)),
            });
    
    keyboardState.macroSet.setMacro(19, MacroType::kInvert, {
            KeyEvent(KeyId(LAlt)),
            KeyEvent(KeyId(F9)),
            });

    auto& layerStack(keyboardState.layerStack);
    
    layerStack.setLayer(0, true);

    layerStack[0].name = "Default";
    layerStack[0].mapping = { {
            { Grave, NonUsHash, K1, K2, K3, K4, K5, NonUsBackslash, KeyId::Lock(KeyId::LockType::kToggle, 8), KeyId::Lock(KeyId::LockType::kToggle, 9),
              Macro(20), Macro(21), KeyId::Layer(5), K6, K7, K8, K9, K0, Minus, Equal },
                
            { Esc, Macro(10), Q, W, E, R, T, Tab, KeyId::Lock(KeyId::LockType::kToggle, 11),0,
              Macro(22), Macro(23), Backspace, Y, U, I, O, P, LBrace, RBrace },
            
            { 0, KeyId::Layer(2), A, S, D, F, G, 0, 0, 0,
              Macro(24), Macro(25), 0, H, J, K, L, Semicolon, Enter },
            
            { 0, KeyId::Lock(kLShift), Z, X, C, V, B, Delete, 0, 0,
              KeyId::Action(KeyId::ActionType::kBuiltIn, 0), KeyId::Action(KeyId::ActionType::kMenu, 0), Quote, N, M, Comma, Dot, Slash, KeyId::Lock(kRShift) },
            
            { 0, KeyId::Lock(kLGui), KeyId::Lock(kRAlt), Macro(26), Macro(27), Macro(28), KeyId::Lock(kLCtrl), KeyId::Layer(1), KeyId::Lock(kLAlt), 0,
              0, KeyId::Lock(kLAlt), Space, KeyId::Lock(kRCtrl), End, Left, Up, Down, Right }
        } };
    
    layerStack[1].name = "Navigation";
    layerStack[1].mapping = { {
            { },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                             /**/ 0, 0, Backspace, PageUp, End, Up, 0, 0, 0 },
            { 0, 0, 0, Macro(0), Macro(1), Macro(2), Macro(3), 0, 0, 0, /**/ 0, 0, 0, Home, Left, Down, Right, 0, 0, 0 },
            { 0, 0, 0, LBrace, RBrace, Macro(4), Macro(5), 0, 0, 0,     /**/ 0, 0, 0, PageDown, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                             /**/ 0, 0, Macro(6), 0, 0, 0, 0, 0, 0, 0 }
        } };

    layerStack[2].name = "Number";
    layerStack[2].mapping = { {
            { 0, 0, 0, 0, 0, 0, 0, 0, F20, F21,       /**/ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, F1, F2, F3, F4, F5, 0, F22, F23,  /**/ 0, 0, 0, 0, K7, K8, K9, 0, 0, 0 },
            { 0, 0, F6, F7, F8, F9, F10, 0, F24, 0,   /**/ 0, 0, 0, 0, K4, K5, K6, 0, 0, 0 },
            { 0, 0, F11, F12, F13, F14, F15, 0, 0, 0, /**/ 0, 0, 0, 0, K1, K2, K3, 0, 0, 0 },
            { 0, 0, F16, F17, F18, F19, 0, 0, 0, 0,   /**/ 0, 0, 0, 0, K0, 0, 0, 0, 0, 0 }
        } };

    layerStack[3].name = "Game";
    layerStack[3].mapping = { {
            { },
            { Esc, 0, Q, W, E, R, T, Tab, 0, 0,        /**/ 0, 0, Backspace, Y, U, I, O, P, LBrace, RBrace },
            { 0, Tab, A, S, D, F, G, 0, 0, 0,          /**/ 0, 0, 0, H, J, K, L, Semicolon, Enter },
            { 0, LShift, Z, X, C, V, B, 0, 0, 0,       /**/ 0, 0, Delete, N, M, Comma, Dot, Slash, RShift },
            { 0, 0, 0, 0, 0, 0, LCtrl, Space, LAlt, 0, /**/ 0, LAlt, Space, RCtrl, End, Left, Up, Down, Right }
        } };

    layerStack[4].name = "Kerbal Space Program";
    layerStack[4].mapping = { {
            { Macro(15),Macro(16), K1, K2, K3, K4, K5, U, 0, 0, /**/ F1, F2, 0, K6, K7, K8, K9, K0, Minus, Equal },
            { Comma, Dot, G, Q, W, E, Insert, Space, 0, 0,      /**/ F3, F4, Backspace, Y, U, I, O, P, LBrace, RBrace },
            { 0, M, KpDot, A, S, D, Delete, 0, 0, Macro(18),    /**/ Macro(19), 0, 0, H, J, K, L, Semicolon, Enter },
            { 0, T, Z, X, C, V, B, Macro(17), Esc, F5,          /**/ F9, 0, Quote, N, M, Comma, Dot, Slash, KeyId::Lock(6) },
            { 0, R, 0, 0, 0, LAlt, LShift, LCtrl, X, 0,         /**/ 0, LAlt, Space, RCtrl, End, Left, Up, Down, Right }
        } };
    
    layerStack[5].name = "Edit";
    layerStack[5].mapping = { {
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                     /**/ EditMacro(20), EditMacro(21), 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                     /**/ EditMacro(22), EditMacro(23), 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                     /**/ EditMacro(24), EditMacro(25), 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                     /**/ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, EditMacro(26), EditMacro(27), EditMacro(28), 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        } };

}

}
