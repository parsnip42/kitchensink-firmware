#include "defaultprofile.h"

#include "keyboardstate.h"

#include "serialize/serializer.h"
#include "types/datarefinstream.h"

namespace DefaultProfile
{

void init(KeyboardState& keyboardState)
{
    static const char* const GlobalConfigTxt =
    "[config]\n"
    "tapDelay=250\n"
    "keyRepeatDelay=660\n"
    "keyRepeatRate=40\n"
    "homeScreenColumns=2\n"
    "homeScreenTimeout=10000\n"

    "[home 0]\n"
    "type=1\n"
    "index=0\n"

    "[home 1]\n"
    "type=2\n"
    "index=0\n"

    "[home 2]\n"
    "type=1\n"
    "index=1\n"

    "[home 3]\n"
    "type=2\n"
    "index=2\n"
    
    "[home 4]\n"
    "type=1\n"
    "index=2\n";

    {
        DataRefInStream is(GlobalConfigTxt);
        Serializer<GlobalConfig> s;

        s.deserialize(is, keyboardState.globalConfig);
    }

    static const char* const LayoutConfig =
    "[layer 0]\n"
    "name=Default\n"
    "row=KGrave KNonUsHash K1 K2 K3 K4 K5 KNonUsBackslash MD10 MD11 MD21 MD22 L3 K6 K7 K8 K9 K0 KMinus KEqual\n"
    "row=KEsc MD7 KQ KW KE KR KT KTab MD12 MD13 MD23 MD24 KBackspace KY KU KI KO KP KLBrace KRBrace\n"
    "row=_ L2 KA KS KD KF KG _ MD14 MD15 U1:4 U1:13 _ KH KJ KK KL KSemicolon KEnter _\n"
    "row=_ N0 KZ KX KC KV KB KDelete MD16 MD17 U0:0 U1:12 KQuote KN KM KComma KDot KSlash N0 _\n"
    "row=_ KLGui KNumLock KCapsLock KScrollLock _ KLCtrl L1 KLAlt _ _ KLAlt KSpace KRCtrl KEnd KLeft KUp KDown KRight _\n"
    
    "[layer 1]\n"
    "name=Navigation\n"
    "row=_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n"
    "row=_ _ _ _ _ _ _ _ _ _ _ _ KBackspace KPageUp KEnd KUp _ _ _ _\n"
    "row=_ _ _ MD0 MD1 MD2 MD3 _ _ _ _ _ _ KHome KLeft KDown KRight _ _ _\n"
    "row=_ _ _ KLBrace KRBrace MD4 MD5 _ _ _ _ _ _ KPageDown _ _ _ _ _ _\n"
    "row=_ _ _ _ _ _ _ _ _ _ _ _ MD6 _ _ _ _ _ _ _\n"
    
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

    {
        DataRefInStream is(LayoutConfig);
        Serializer<LayerStack> s;

        s.deserialize(is, keyboardState.layerStack);
    }

    static const char* const MacroConfig =
    "[macro 0]\n"
    "name={\n"
    "shortcut=\n"
    "type=2\n"
    "content=KLShift KLBrace\n"

    "[macro 1]\n"
    "name=}\n"
    "shortcut=\n"
    "type=2\n"
    "content=KLShift KRBrace\n"

    "[macro 2]\n"
    "name=(\n"
    "shortcut=\n"
    "type=2\n"
    "content=KLShift K9\n"

    "[macro 3]\n"
    "name=)\n"
    "shortcut=\n"
    "type=2\n"
    "content=KLShift K0\n"

    "[macro 4]\n"
    "name=<\n"
    "shortcut=\n"
    "type=2\n"
    "content=KLShift KComma\n"

    "[macro 5]\n"
    "name=>\n"
    "shortcut=\n"
    "type=2\n"
    "content=KLShift KDot\n"

    "[macro 6]\n"
    "name=Ctrl+Spc\n"
    "shortcut=\n"
    "type=2\n"
    "content=KLCtrl KSpace\n"

    "[macro 7]\n"
    "name=_\n"
    "shortcut=\n"
    "type=2\n"
    "content=KLShift KMinus\n"

    "[macro 8]\n"; // FIXME!
    
    {
        DataRefInStream is(MacroConfig);
        Serializer<MacroSet> s;
    
        s.deserialize(is, keyboardState.macroSet);
    }
    
    static const char* const MultiConfig =
    "[multi 0]\n"
    "name=Shift\n"
    "event=KLShift\n"
    "event=_\n"
    "event=S0\n"
    "event=_\n"

    "[multi 1]\n"
    "name=Num Toggle\n"
    "event=L2\n"
    "event=_\n"
    "event=S1\n"
    "event=_\n";
    
    {
        DataRefInStream is(MultiConfig);
        Serializer<MultiKeySet> s;
    
        s.deserialize(is, keyboardState.multiKeySet);
    }

    static const char* const SmartConfig =
    "[smart 0]\n"
    "name=Shift Lock\n"
    "event=KLShift\n"
    "auxEvent=_\n"
    
    "[smart 1]\n"
    "name=Num Toggle\n"
    "event=L2\n"
    "auxEvent=_\n";

    {
        DataRefInStream is(SmartConfig);
        Serializer<SmartKeySet> s;
    
        s.deserialize(is, keyboardState.smartKeySet);
    }
}

}
