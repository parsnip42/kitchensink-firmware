#include "defaultprofile.h"

#include "keyboardstate.h"
#include "data/keycodes.h"

#include "event/event.h"
#include "event/keyevent.h"
#include "event/actionevent.h"
#include "event/multievent.h"
#include "event/screenevent.h"
#include "event/layerevent.h"
#include "event/macroevent.h"
#include "event/smartevent.h"

namespace DefaultProfile
{

namespace
{
constexpr Event Macro(int macroId)
{
    return MacroEvent::create(macroId);
}

constexpr Event Layer(int layerId)
{
    return LayerEvent::create(layerId);
}

constexpr Event Bootloader()
{
    return ActionEvent::create(0);
}

constexpr Event Multi(int index)
{
    return MultiEvent::create(index);
}

constexpr Event MainMenu()
{
    return ScreenEvent::create(ScreenEvent::Type::kHome, 0);
}

constexpr Event Menu(int index)
{
    return ScreenEvent::create(ScreenEvent::Type::kMenu, index);
}

constexpr Event EditMacro(int macroId)
{
    return ScreenEvent::create(ScreenEvent::Type::kEditMacro, macroId);
}

}

void init(KeyboardState& keyboardState)
{
    auto& macroSet(keyboardState.macroSet);
    
    {
        auto& macro(macroSet[0]);

        macro.type = Macro::Type::kInvert;
        macro.name = "{";
        macro.content = {
            KeyCode::LShift,
            KeyCode::LBrace
        };
    }
    
    {
        auto& macro(macroSet[1]);

        macro.type = Macro::Type::kInvert;
        macro.name = "}";
        macro.content = {
            KeyCode::LShift,
            KeyCode::RBrace
        };
    }
    
    {
        auto& macro(macroSet[2]);

        macro.type = Macro::Type::kInvert;
        macro.name = "(";
        macro.content = {
            KeyCode::LShift,
            KeyCode::K9
        };
    }

  {
        auto& macro(macroSet[3]);

        macro.type = Macro::Type::kInvert;
        macro.name = ")";
        macro.content = {
            KeyCode::LShift,
            KeyCode::K0
        };
    }

    {
        auto& macro(macroSet[4]);

        macro.type = Macro::Type::kInvert;
        macro.name = "<";
        macro.content = {
            KeyCode::LShift,
            KeyCode::Comma
        };
    }

    {
        auto& macro(macroSet[5]);

        macro.type = Macro::Type::kInvert;
        macro.name = ">";
        macro.content = {
            KeyCode::LShift,
            KeyCode::Dot
        };
    }

    {
        auto& macro(macroSet[6]);

        macro.type = Macro::Type::kInvert;
        macro.name = "Ctrl+Spc";
        macro.content = {
            KeyCode::LCtrl,
            KeyCode::Space
        };
    }

    {
        auto& macro(macroSet[7]);

        macro.type = Macro::Type::kInvert;
        macro.name = "_";
        macro.content = {
            KeyCode::LShift,
            KeyCode::Minus
        };
    }

    keyboardState.multiSet[0].name = "Shift";
    keyboardState.multiSet[0].events[0] = KeyCode::LShift;
    keyboardState.multiSet[0].events[2] = SmartEvent::create(0);
    
    keyboardState.smartKeySet[0].name = "Shift Lock";
    keyboardState.smartKeySet[0].type = SmartKey::Type::kToggle;
    keyboardState.smartKeySet[0].event = KeyCode::LShift;

    keyboardState.multiSet[2].name = "Num Toggle";
    keyboardState.multiSet[2].events[0] = Layer(2);
    keyboardState.multiSet[2].events[2] = SmartEvent::create(2);
    
    keyboardState.smartKeySet[2].name = "Num Toggle";
    keyboardState.smartKeySet[2].type = SmartKey::Type::kToggle;
    keyboardState.smartKeySet[2].event = Layer(2);

    auto& layerStack(keyboardState.layerStack);
    
    layerStack[0].name = "Default";
    layerStack[0].mapping = { {
            { { KeyCode::Grave, KeyCode::NonUsHash, KeyCode::K1, KeyCode::K2, KeyCode::K3, KeyCode::K4, KeyCode::K5, KeyCode::NonUsBackslash, Macro(10), Macro(11), /**/ Macro(21), Macro(22),Layer(3), KeyCode::K6, KeyCode::K7, KeyCode::K8, KeyCode::K9, KeyCode::K0, KeyCode::Minus, KeyCode::Equal } },
            { { KeyCode::Esc, Macro(7), KeyCode::Q, KeyCode::W, KeyCode::E, KeyCode::R, KeyCode::T, KeyCode::Tab, Macro(12), Macro(13),                    /**/ Macro(23), Macro(24), KeyCode::Backspace, KeyCode::Y, KeyCode::U, KeyCode::I, KeyCode::O, KeyCode::P, KeyCode::LBrace, KeyCode::RBrace } },
            { { KeyCode::_, Layer(2), KeyCode::A, KeyCode::S, KeyCode::D, KeyCode::F, KeyCode::G, KeyCode::_, Macro(14), Macro(15),                       /**/ Macro(25), Menu(3), KeyCode::_, KeyCode::H, KeyCode::J, KeyCode::K, KeyCode::L, KeyCode::Semicolon, KeyCode::Enter } },
            { { KeyCode::_, Multi(0), KeyCode::Z, KeyCode::X, KeyCode::C, KeyCode::V, KeyCode::B, KeyCode::Delete, Macro(16), Macro(17),                   /**/ MainMenu(), Menu(12), KeyCode::Quote, KeyCode::N, KeyCode::M, KeyCode::Comma, KeyCode::Dot, KeyCode::Slash, Multi(0) } },
            { { KeyCode::_, KeyCode::LGui, KeyCode::NumLock, KeyCode::CapsLock, KeyCode::ScrollLock, KeyCode::_,
                KeyCode::LCtrl, Layer(1), KeyCode::LAlt, KeyCode::_,                                    /**/ KeyCode::_ , KeyCode::LAlt, KeyCode::Space, KeyCode::RCtrl, KeyCode::End, KeyCode::Left, KeyCode::Up, KeyCode::Down, KeyCode::Right } }
        } };
    
    layerStack[1].name = "Navigation";
    layerStack[1].mapping = { {
            { },
            { { KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_,                             /**/ KeyCode::_, KeyCode::_, KeyCode::Backspace, KeyCode::PageUp, KeyCode::End, KeyCode::Up, KeyCode::_, KeyCode::_, KeyCode::_ } },
            { { KeyCode::_, KeyCode::_, KeyCode::_, Macro(0), Macro(1), Macro(2), Macro(3), KeyCode::_, KeyCode::_, KeyCode::_, /**/ KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::Home, KeyCode::Left, KeyCode::Down, KeyCode::Right, KeyCode::_, KeyCode::_, KeyCode::_ } },
            { { KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::LBrace, KeyCode::RBrace, Macro(4), Macro(5), KeyCode::_, KeyCode::_, KeyCode::_,     /**/ KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::PageDown, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_ } },
            { { KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_,                             /**/ KeyCode::_, KeyCode::_, Macro(6), KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_ } }
        } };

    layerStack[2].name = "Number";
    layerStack[2].mapping = { {
            { { KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::F20, KeyCode::F21,       /**/ KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_ } },
            { { KeyCode::_, KeyCode::_, KeyCode::F1, KeyCode::F2, KeyCode::F3, KeyCode::F4, KeyCode::F5, KeyCode::_, KeyCode::F22, KeyCode::F23,  /**/ KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::K7, KeyCode::K8, KeyCode::K9, KeyCode::_, KeyCode::_, KeyCode::_ } },
            { { KeyCode::_, KeyCode::_, KeyCode::F6, KeyCode::F7, KeyCode::F8, KeyCode::F9, KeyCode::F10, KeyCode::_, KeyCode::F24, KeyCode::_,   /**/ KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::K4, KeyCode::K5, KeyCode::K6, KeyCode::_, KeyCode::_, KeyCode::_ } },
            { { KeyCode::_, KeyCode::_, KeyCode::F11, KeyCode::F12, KeyCode::F13, KeyCode::F14, KeyCode::F15, KeyCode::_, KeyCode::_, KeyCode::_, /**/ KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::K1, KeyCode::K2, KeyCode::K3, KeyCode::_, KeyCode::_, KeyCode::_ } },
            { { KeyCode::_, KeyCode::_, KeyCode::F16, KeyCode::F17, KeyCode::F18, KeyCode::F19, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_,   /**/ KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::K0, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_ } }
        } };

    layerStack[3].name = "Edit";
    layerStack[3].mapping = { {
            { { KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, EditMacro(10), EditMacro(11),             /**/ EditMacro(21), EditMacro(22), KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_ } },
            { { KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, EditMacro(12), EditMacro(13),             /**/ EditMacro(23), EditMacro(24), KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_ } },
            { { KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, EditMacro(14), EditMacro(15),             /**/ EditMacro(25), KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_ } },
            { { KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, EditMacro(16), EditMacro(17),             /**/ Bootloader(),  Menu(2), KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_ } },
            { { KeyCode::_, KeyCode::_, KeyCode::_, EditMacro(18), EditMacro(19), EditMacro(20), KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, /**/ KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_, KeyCode::_ } },
        } };
}

}
