#include "keycodes.h"

namespace KeyCodes
{
namespace
{

const char* const Keys[] =
{
    "None",
    "ErrorRollOver",
    "PostFail",
    "ErrorUndefined",
    "A",
    "B",
    "C",
    "D",
    "E",
    "F",
    "G",
    "H",
    "I",
    "J",
    "K",
    "L",
    "M",
    "N",
    "O",
    "P",
    "Q",
    "R",
    "S",
    "T",
    "U",
    "V",
    "W",
    "X",
    "Y",
    "Z",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "0",
    "Enter",
    "Esc",
    "Backspace",
    "Tab",
    "Space",
    "Minus",
    "Equal",
    "LBrace",
    "RBrace",
    "Backslash",
    "NonUsHash",
    "Semicolon",
    "Quote",
    "Grave",
    "Comma",
    "Dot",
    "Slash",
    "CapsLock",
    "F1",
    "F2",
    "F3",
    "F4",
    "F5",
    "F6",
    "F7",
    "F8",
    "F9",
    "F10",
    "F11",
    "F12",
    "PrintScreen",
    "ScrollLock",
    "Pause",
    "Insert",
    "Home",
    "PageUp",
    "Delete",
    "End",
    "PageDown",
    "Right",
    "Left",
    "Down",
    "Up",
    "NumLock",
    "KpSlash",
    "KpAsterisk",
    "KpMinus",
    "KpPlus",
    "KpEnter",
    "Kp1",
    "Kp2",
    "Kp3",
    "Kp4",
    "Kp5",
    "Kp6",
    "Kp7",
    "Kp8",
    "Kp9",
    "Kp0",
    "KpDot",
    "NonUsBackslash",
    "Application",
    "Power",
    "KpEqual",
    "F13",
    "F14",
    "F15",
    "F16",
    "F17",
    "F18",
    "F19",
    "F20",
    "F21",
    "F22",
    "F23",
    "F24",
    "Execute",
    "Help",
    "Menu",
    "Select",
    "Stop",
    "Again",
    "Undo",
    "Cut",
    "Copy",
    "Paste",
    "Find",
    "Mute",
    "VolumeUp",
    "VolumeDown",
    "LockCapsLock",
    "LockNumLock",
    "LockScrollLock",
    "KpComma",
    "KpEqualSign",
    "International1",
    "International2",
    "International3",
    "International4",
    "International5",
    "International6",
    "International7",
    "International8",
    "International9",
    "Lang1",
    "Lang2",
    "Lang3",
    "Lang4",
    "Lang5",
    "Lang6",
    "Lang7",
    "Lang8",
    "Lang9",
    "AltErase",
    "SysReq",
    "Cancel",
    "Clear",
    "Prior",
    "Return",
    "Separator",
    "Out",
    "Oper",
    "ClearAgain",
    "CrSel",
    "ExSel"
};

const std::size_t KeyCount(sizeof(Keys) / sizeof(*Keys));

const char* const Modifiers[] =
{
    "LCtrl",
    "LShift",
    "LAlt",
    "LGui",
    "RCtrl",
    "RShift",
    "RAlt",
    "RGui"
};

const std::size_t ModifierCount(sizeof(Modifiers) / sizeof(*Modifiers));
}

StrRef keyName(keycode_t keyCode)
{
    if (keyCode < KeyCount)
    {
        return Keys[keyCode];
    }
    else if ((keyCode >= ModifierOffset) &&
             (keyCode < (ModifierOffset + ModifierCount)))
    {
        return Modifiers[keyCode - ModifierOffset];
    }
    
    return StrRef();
}

keycode_t keyCode(const StrRef& keyName)
{
    // Intentionally avoiding the use of a lookup table to save
    // memory. If performance becomes a problem, we should create an
    // ordered index for a binary search.
    for (keycode_t i(0); i < KeyCount; ++i)
    {
        // And this might need to be case-insensitive too.
        if (keyName == Keys[i])
        {
            return i;
        }
    }

    for (keycode_t i(0); i < ModifierCount; ++i)
    {
        if (keyName == Modifiers[i])
        {
            return i + ModifierOffset;
        }
    }

    return 0;
}

}
