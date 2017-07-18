#include "defaultprofile.h"

#include "keyid.h"
#include "keyboardstate.h"
#include "data/keycodes.h"

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

constexpr KeyId Layer(int layerId)
{
    return KeyId::Layer(layerId);
}

constexpr KeyId Hold(int lockId)
{
    return KeyId::Lock(lockId);
}

constexpr KeyId Toggle(int lockId)
{
    return KeyId::Lock(KeyId::LockType::kToggle, lockId);
}

constexpr KeyId Bootloader()
{
    return KeyId::Action(KeyId::ActionType::kBuiltIn, 0);
}

constexpr KeyId MainMenu()
{
    return KeyId::Action(KeyId::ActionType::kMenu, 0);
}

constexpr KeyId Menu(int index)
{
    return KeyId::Action(KeyId::ActionType::kMenu, index);
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

    keyboardState.lockSet[8] = Lock("Game", KeyId::Layer(4));

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

    keyboardState.macroSet.setMacro(4, MacroType::kInvert, "<",{
            KeyEvent(KeyId(LShift)),
            KeyEvent(KeyId(Comma)),
            });

    keyboardState.macroSet.setMacro(5, MacroType::kInvert, ">", {
            KeyEvent(KeyId(LShift)),
            KeyEvent(KeyId(Dot)),
            });
    
    keyboardState.macroSet.setMacro(6, MacroType::kInvert, "Ctrl+Spc", {
            KeyEvent(KeyId(LCtrl)),
            KeyEvent(KeyId(Space)),
            });

    keyboardState.macroSet.setMacro(7, MacroType::kInvert, "_", {
            KeyEvent(KeyId(LShift)),
            KeyEvent(KeyId(Minus)),
            });

    auto& layerStack(keyboardState.layerStack);
    
    layerStack.setLayer(0, true);

    layerStack[0].name = "Default";
    layerStack[0].mapping = { {
            { { Grave, NonUsHash, K1, K2, K3, K4, K5, NonUsBackslash, Macro(10), Macro(11), /**/ Macro(21),  Macro(22), Layer(3), K6, K7, K8, K9, K0, Minus, Equal } },
            { { Esc, Macro(7), Q, W, E, R, T, Tab, Macro(12), Macro(13),                    /**/ Macro(23),  Macro(24), Backspace, Y, U, I, O, P, LBrace, RBrace } },
            { { 0, Layer(2), A, S, D, F, G, 0, Macro(14), Macro(15),                        /**/ Macro(25),  Macro(26), 0, H, J, K, L, Semicolon, Enter } },
            { { 0, Hold(kLShift), Z, X, C, V, B, 0, Macro(16), Macro(17),                   /**/ MainMenu(), Menu(1), Quote, N, M, Comma, Dot, Slash, Hold(kRShift) } },
            { { 0, Y, U, I, O, P,
                Hold(kLCtrl), Layer(1), Hold(kLAlt), 0,                                     /**/ 0, Hold(kLAlt), Space, Hold(kRCtrl), End, Left, Up, Down, Right } }
        } };
    
    layerStack[1].name = "Navigation";
    layerStack[1].mapping = { {
            { },
            { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                             /**/ 0, 0, Backspace, PageUp, End, Up, 0, 0, 0 } },
            { { 0, 0, 0, Macro(0), Macro(1), Macro(2), Macro(3), 0, 0, 0, /**/ 0, 0, 0, Home, Left, Down, Right, 0, 0, 0 } },
            { { 0, 0, 0, LBrace, RBrace, Macro(4), Macro(5), 0, 0, 0,     /**/ 0, 0, 0, PageDown, 0, 0, 0, 0, 0, 0 } },
            { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                             /**/ 0, 0, Macro(6), 0, 0, 0, 0, 0, 0, 0 } }
        } };

    layerStack[2].name = "Number";
    layerStack[2].mapping = { {
            { { 0, 0, 0, 0, 0, 0, 0, 0, F20, F21,       /**/ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
            { { 0, 0, F1, F2, F3, F4, F5, 0, F22, F23,  /**/ 0, 0, 0, 0, K7, K8, K9, 0, 0, 0 } },
            { { 0, 0, F6, F7, F8, F9, F10, 0, F24, 0,   /**/ 0, 0, 0, 0, K4, K5, K6, 0, 0, 0 } },
            { { 0, 0, F11, F12, F13, F14, F15, 0, 0, 0, /**/ 0, 0, 0, 0, K1, K2, K3, 0, 0, 0 } },
            { { 0, 0, F16, F17, F18, F19, 0, 0, 0, 0,   /**/ 0, 0, 0, 0, K0, 0, 0, 0, 0, 0 } }
        } };

    layerStack[3].name = "Edit";
    layerStack[3].mapping = { {
            { { 0, 0, 0, 0, 0, 0, 0, 0, EditMacro(10), EditMacro(11),             /**/ EditMacro(21), EditMacro(22), 0, 0, 0, 0, 0, 0, 0, 0 } },
            { { 0, 0, 0, 0, 0, 0, 0, 0, EditMacro(12), EditMacro(13),             /**/ EditMacro(23), EditMacro(24), 0, 0, 0, 0, 0, 0, 0, 0 } },
            { { 0, 0, 0, 0, 0, 0, 0, 0, EditMacro(14), EditMacro(15),             /**/ EditMacro(25), EditMacro(26), 0, 0, 0, 0, 0, 0, 0, 0 } },
            { { 0, 0, 0, 0, 0, 0, 0, 0, EditMacro(16), EditMacro(17),             /**/ Bootloader(),  Menu(2), 0, 0, 0, 0, 0, 0, 0, 0 } },
            { { 0, 0, 0, EditMacro(18), EditMacro(19), EditMacro(20), 0, 0, 0, 0, /**/ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
        } };

    layerStack[4].name = "Game";
    layerStack[4].mapping = { {
            { },
            { { Esc, 0, Q, W, E, R, T, Tab, 0, 0,        /**/ 0, 0, Backspace, Y, U, I, O, P, LBrace, RBrace } },
            { { 0, Tab, A, S, D, F, G, 0, 0, 0,          /**/ 0, 0, 0, H, J, K, L, Semicolon, Enter } },
            { { 0, LShift, Z, X, C, V, B, 0, 0, 0,       /**/ 0, 0, Delete, N, M, Comma, Dot, Slash, RShift } },
            { { 0, 0, 0, 0, 0, 0, LCtrl, Space, LAlt, 0, /**/ 0, LAlt, Space, RCtrl, End, Left, Up, Down, Right } }
        } };
}

}
