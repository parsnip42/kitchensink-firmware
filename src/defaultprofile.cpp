#include "defaultprofile.h"

#include "keyboardstate.h"
#include "data/keycode.h"

#include "event/event.h"
#include "event/keyevent.h"
#include "event/actionevent.h"
#include "event/multievent.h"
#include "event/screenevent.h"
#include "event/layerevent.h"
#include "event/macroevent.h"
#include "event/smartevent.h"

#include "layer.h"

#include "serialize/serializer.h"
#include "types/strinstream.h"

namespace DefaultProfile
{

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
    keyboardState.multiSet[2].events[0] = LayerEvent::create(2);
    keyboardState.multiSet[2].events[2] = SmartEvent::create(2);
    
    keyboardState.smartKeySet[2].name = "Num Toggle";
    keyboardState.smartKeySet[2].type = SmartKey::Type::kToggle;
    keyboardState.smartKeySet[2].event = LayerEvent::create(2);

    static const char* const LayoutConfig =
    "[layer 0]\n"
    "name=Default\n"
    "row=KGrave KNonUsHash K1 K2 K3 K4 K5 KNonUsBackslash M10 M11 M21 M22 L3 K6 K7 K8 K9 K0 KMinus KEqual\n"
    "row=KEsc M7 KQ KW KE KR KT KTab M12 M13 M23 M24 KBackspace KY KU KI KO KP KLBrace KRBrace\n"
    "row=_ L2 KA KS KD KF KG _ M14 M15 M25 U1:3 _ KH KJ KK KL KSemicolon KEnter _\n"
    "row=_ N0 KZ KX KC KV KB KDelete M16 M17 U0:0 U1:12 KQuote KN KM KComma KDot KSlash N0 _\n"
    "row=_ KLGui KNumLock KCapsLock KScrollLock _ KLCtrl L1 KLAlt _ _ KLAlt KSpace KRCtrl KEnd KLeft KUp KDown KRight _\n"
    
    "[layer 1]\n"
    "name=Navigation\n"
    "row=_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n"
    "row=_ _ _ _ _ _ _ _ _ _ _ _ KBackspace KPageUp KEnd KUp _ _ _ _\n"
    "row=_ _ _ M0 M1 M2 M3 _ _ _ _ _ _ KHome KLeft KDown KRight _ _ _\n"
    "row=_ _ _ KLBrace KRBrace M4 M5 _ _ _ _ _ _ KPageDown _ _ _ _ _ _\n"
    "row=_ _ _ _ _ _ _ _ _ _ _ _ M6 _ _ _ _ _ _ _\n"
    
    "[layer 2]\n"
    "name=Number\n"
    "row=_ _ _ _ _ _ _ _ KF20 KF21 _ _ _ _ _ _ _ _ _ _\n"
    "row=_ _ KF1 KF2 KF3 KF4 KF5 _ KF22 KF23 _ _ _ _ K7 K8 K9 _ _ _\n"
    "row=_ _ KF6 KF7 KF8 KF9 KF10 _ KF24 _ _ _ _ _ K4 K5 K6 _ _ _\n"
    "row=_ _ KF11 KF12 KF13 KF14 KF15 _ _ _ _ _ _ _ K1 K2 K3 _ _ _\n"
    "row=_ _ KF16 KF17 KF18 KF19 _ _ _ _ _ _ _ _ K0 _ _ _ _ _\n"

    "[layer 3]\n"
    "name=Edit\n"
    "row=_ _ _ _ _ _ _ _ U3:10 U3:11 U3:21 U3:22 _ _ _ _ _ _ _ _\n"
    "row=_ _ _ _ _ _ _ _ U3:12 U3:13 U3:23 U3:24 _ _ _ _ _ _ _ _\n"
    "row=_ _ _ _ _ _ _ _ U3:14 U3:15 U3:25 _ _ _ _ _ _ _ _ _\n"
    "row=_ _ _ _ _ _ _ _ U3:16 U3:17 A0 U1:2 _ _ _ _ _ _ _ _\n"
    "row=_ _ _ U3:18 U3:19 U3:20 _ _ _ _ _ _ _ _ _ _ _ _ _ _\n";

    StrInStream is(LayoutConfig);
    
    Serializer<LayerStack> s;

    s.deserialize(is, keyboardState.layerStack);
}

}
