#include "defaultprofile.h"

#include "keyid.h"
#include "keyboardstate.h"
#include "data/keycodes.h"

namespace DefaultProfile
{

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

constexpr KeyId Multi(int index)
{
    return KeyId::Multi(index);
}

}

void init(KeyboardState& keyboardState)
{
    using namespace KeyCodes;

    auto& macroSet(keyboardState.macroSet);
    
    {
        auto& macro(macroSet[0]);

        macro.type = MacroType::kInvert;
        macro.name = "{";
        macro.content = {
            KeyEvent(KeyId(LShift)),
            KeyEvent(KeyId(LBrace)),
        };
    }
    
    {
        auto& macro(macroSet[1]);

        macro.type = MacroType::kInvert;
        macro.name = "}";
        macro.content = {
            KeyEvent(KeyId(LShift)),
            KeyEvent(KeyId(RBrace)),
        };
    }
    
    {
        auto& macro(macroSet[2]);

        macro.type = MacroType::kInvert;
        macro.name = "(";
        macro.content = {
            KeyEvent(KeyId(LShift)),
            KeyEvent(KeyId(K9)),
        };
    }

  {
        auto& macro(macroSet[3]);

        macro.type = MacroType::kInvert;
        macro.name = ")";
        macro.content = {
            KeyEvent(KeyId(LShift)),
            KeyEvent(KeyId(K0)),
        };
    }

    {
        auto& macro(macroSet[4]);

        macro.type = MacroType::kInvert;
        macro.name = "<";
        macro.content = {
            KeyEvent(KeyId(LShift)),
            KeyEvent(KeyId(Comma)),
        };
    }

    {
        auto& macro(macroSet[5]);

        macro.type = MacroType::kInvert;
        macro.name = ">";
        macro.content = {
            KeyEvent(KeyId(LShift)),
            KeyEvent(KeyId(Dot)),
        };
    }

    {
        auto& macro(macroSet[6]);

        macro.type = MacroType::kInvert;
        macro.name = "Ctrl+Spc";
        macro.content = {
            KeyEvent(KeyId(LCtrl)),
            KeyEvent(KeyId(Space)),
        };
    }

    {
        auto& macro(macroSet[7]);

        macro.type = MacroType::kInvert;
        macro.name = "_";
        macro.content = {
            KeyEvent(KeyId(LShift)),
            KeyEvent(KeyId(Minus)),
        };
    }

    keyboardState.multiSet[0].keys[0] = LShift;
    keyboardState.multiSet[0].keys[2] = KeyId::Smart(0);
    
    keyboardState.smartKeySet[0].name = "LShift Toggle";
    keyboardState.smartKeySet[0].type = SmartKey::Type::kToggle;
    keyboardState.smartKeySet[0].keyId = LShift;
    
    keyboardState.multiSet[1].keys[0] = RShift;
    keyboardState.multiSet[1].keys[2] = KeyId::Smart(1);

    keyboardState.smartKeySet[1].name = "RShift Toggle";
    keyboardState.smartKeySet[1].type = SmartKey::Type::kToggle;
    keyboardState.smartKeySet[1].keyId = RShift;        

    keyboardState.multiSet[2].keys[0] = MainMenu();
    keyboardState.multiSet[2].keys[1] = Bootloader();

    auto& layerStack(keyboardState.layerStack);
    
    layerStack[0].name = "Default";
    layerStack[0].mapping = { {
            { { Grave, NonUsHash, K1, K2, K3, K4, K5, NonUsBackslash, Macro(10), Macro(11), /**/ Macro(21),  Macro(22), Layer(3), K6, K7, K8, K9, K0, Minus, Equal } },
            { { Esc, Macro(7), Q, W, E, R, T, Tab, Macro(12), Macro(13),                    /**/ Macro(23),  Macro(24), Backspace, Y, U, I, O, P, LBrace, RBrace } },
            { { 0, Layer(2), A, S, D, F, G, 0, Macro(14), Macro(15),                        /**/ Macro(25),  Macro(26), 0, H, J, K, L, Semicolon, Enter } },
            { { 0, Multi(0), Z, X, C, V, B, Delete, Macro(16), Macro(17),                   /**/ Multi(2), Menu(1), Quote, N, M, Comma, Dot, Slash, Multi(1) } },
            { { 0, Y, U, I, O, P,
                LCtrl, Layer(1), LAlt, 0,                                     /**/ 0,LAlt, Space, RCtrl, End, Left, Up, Down, Right } }
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
