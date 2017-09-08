#ifndef INCLUDED_KEYCODES_H
#define INCLUDED_KEYCODES_H

#include "types/strref.h"

#include <cstdint>

enum class KeyCode : uint8_t
{
    _              = 0x00,
    None           = 0x00, // Reserved (no event indicated)
    ErrorRollOver  = 0x01, // Keyboard ErrorRollOver
    PostFail       = 0x02, // Keyboard POSTFail
    ErrorUndefined = 0x03, // Keyboard ErrorUndefined
    A              = 0x04, // Keyboard a and A
    B              = 0x05, // Keyboard b and B
    C              = 0x06, // Keyboard c and C
    D              = 0x07, // Keyboard d and D
    E              = 0x08, // Keyboard e and E
    F              = 0x09, // Keyboard f and F
    G              = 0x0a, // Keyboard g and G
    H              = 0x0b, // Keyboard h and H
    I              = 0x0c, // Keyboard i and I
    J              = 0x0d, // Keyboard j and J
    K              = 0x0e, // Keyboard k and K
    L              = 0x0f, // Keyboard l and L
    M              = 0x10, // Keyboard m and M
    N              = 0x11, // Keyboard n and N
    O              = 0x12, // Keyboard o and O
    P              = 0x13, // Keyboard p and P
    Q              = 0x14, // Keyboard q and Q
    R              = 0x15, // Keyboard r and R
    S              = 0x16, // Keyboard s and S
    T              = 0x17, // Keyboard t and T
    U              = 0x18, // Keyboard u and U
    V              = 0x19, // Keyboard v and V
    W              = 0x1a, // Keyboard w and W
    X              = 0x1b, // Keyboard x and X
    Y              = 0x1c, // Keyboard y and Y
    Z              = 0x1d, // Keyboard z and Z
    K1             = 0x1e, // Keyboard 1 and !
    K2             = 0x1f, // Keyboard 2 and @
    K3             = 0x20, // Keyboard 3 and #
    K4             = 0x21, // Keyboard 4 and $
    K5             = 0x22, // Keyboard 5 and %
    K6             = 0x23, // Keyboard 6 and ^
    K7             = 0x24, // Keyboard 7 and &
    K8             = 0x25, // Keyboard 8 and *
    K9             = 0x26, // Keyboard 9 and (
    K0             = 0x27, // Keyboard 0 and )
    Enter          = 0x28, // Keyboard Return (ENTER)
    Esc            = 0x29, // Keyboard ESCAPE
    Backspace      = 0x2a, // Keyboard DELETE (Backspace)
    Tab            = 0x2b, // Keyboard Tab
    Space          = 0x2c, // Keyboard Spacebar
    Minus          = 0x2d, // Keyboard - and (underscore)
    Equal          = 0x2e, // Keyboard = and +
    LBrace         = 0x2f, // Keyboard [ and {
    RBrace         = 0x30, // Keyboard ] and }
    Backslash      = 0x31, // Keyboard \ and |
    NonUsHash      = 0x32, // Keyboard Non-US # and ~
    Semicolon      = 0x33, // Keyboard , and :
    Quote          = 0x34, // Keyboard ' and "
    Grave          = 0x35, // Keyboard Grave Accent and Tilde
    Comma          = 0x36, // Keyboard , and <
    Dot            = 0x37, // Keyboard . and >
    Slash          = 0x38, // Keyboard / and ?
    CapsLock       = 0x39, // Keyboard Caps Lock
    F1             = 0x3a, // Keyboard F1
    F2             = 0x3b, // Keyboard F2
    F3             = 0x3c, // Keyboard F3
    F4             = 0x3d, // Keyboard F4
    F5             = 0x3e, // Keyboard F5
    F6             = 0x3f, // Keyboard F6
    F7             = 0x40, // Keyboard F7
    F8             = 0x41, // Keyboard F8
    F9             = 0x42, // Keyboard F9
    F10            = 0x43, // Keyboard F10
    F11            = 0x44, // Keyboard F11
    F12            = 0x45, // Keyboard F12
    PrintScreen    = 0x46, // Keyboard PrintScreen
    ScrollLock     = 0x47, // Keyboard Scroll Lock
    Pause          = 0x48, // Keyboard Pause
    Insert         = 0x49, // Keyboard Insert
    Home           = 0x4a, // Keyboard Home
    PageUp         = 0x4b, // Keyboard PageUp
    Delete         = 0x4c, // Keyboard Delete Forward
    End            = 0x4d, // Keyboard End
    PageDown       = 0x4e, // Keyboard PageDown
    Right          = 0x4f, // Keyboard RightArrow
    Left           = 0x50, // Keyboard LeftArrow
    Down           = 0x51, // Keyboard DownArrow
    Up             = 0x52, // Keyboard UpArrow
    NumLock        = 0x53, // Keypad Num Lock and Clear
    KpSlash        = 0x54, // Keypad /
    KpAsterisk     = 0x55, // Keypad *
    KpMinus        = 0x56, // Keypad -
    KpPlus         = 0x57, // Keypad +
    KpEnter        = 0x58, // Keypad ENTER
    Kp1            = 0x59, // Keypad 1 and End
    Kp2            = 0x5a, // Keypad 2 and Down Arrow
    Kp3            = 0x5b, // Keypad 3 and PageDn
    Kp4            = 0x5c, // Keypad 4 and Left Arrow
    Kp5            = 0x5d, // Keypad 5
    Kp6            = 0x5e, // Keypad 6 and Right Arrow
    Kp7            = 0x5f, // Keypad 7 and Home
    Kp8            = 0x60, // Keypad 8 and Up Arrow
    Kp9            = 0x61, // Keypad 9 and PageUp
    Kp0            = 0x62, // Keypad 0 and Insert
    KpDot          = 0x63, // Keypad . and Delete
    NonUsBackslash = 0x64, // Keyboard Non-US \ and |
    Application    = 0x65, // Keyboard Application
    Power          = 0x66, // Keyboard Power
    KpEqual        = 0x67, // Keypad =
    F13            = 0x68, // Keyboard F13
    F14            = 0x69, // Keyboard F14
    F15            = 0x6a, // Keyboard F15
    F16            = 0x6b, // Keyboard F16
    F17            = 0x6c, // Keyboard F17
    F18            = 0x6d, // Keyboard F18
    F19            = 0x6e, // Keyboard F19
    F20            = 0x6f, // Keyboard F20
    F21            = 0x70, // Keyboard F21
    F22            = 0x71, // Keyboard F22
    F23            = 0x72, // Keyboard F23
    F24            = 0x73, // Keyboard F24
    Execute        = 0x74, // Keyboard Execute
    Help           = 0x75, // Keyboard Help
    Menu           = 0x76, // Keyboard Menu
    Select         = 0x77, // Keyboard Select
    Stop           = 0x78, // Keyboard Stop
    Again          = 0x79, // Keyboard Again
    Undo           = 0x7a, // Keyboard Undo
    Cut            = 0x7b, // Keyboard Cut
    Copy           = 0x7c, // Keyboard Copy
    Paste          = 0x7d, // Keyboard Paste
    Find           = 0x7e, // Keyboard Find
    Mute           = 0x7f, // Keyboard Mute
    VolumeUp       = 0x80, // Keyboard Volume Up
    VolumeDown     = 0x81, // Keyboard Volume Down
    LockCapsLock   = 0x82, // Keyboard Locking Caps Lock
    LockNumLock    = 0x83, // Keyboard Locking Num Lock
    LockScrollLock = 0x84, // Keyboard Locking Scroll Lock
    KpComma        = 0x85, // Keypad Comma
    KpEqualSign    = 0x86, // Keypad Equal Sign
    International1 = 0x87, // Keyboard International1
    International2 = 0x88, // Keyboard International2
    International3 = 0x89, // Keyboard International3
    International4 = 0x8a, // Keyboard International4
    International5 = 0x8b, // Keyboard International5
    International6 = 0x8c, // Keyboard International6
    International7 = 0x8d, // Keyboard International7
    International8 = 0x8e, // Keyboard International8
    International9 = 0x8f, // Keyboard International9
    Lang1          = 0x90, // Keyboard LANG1
    Lang2          = 0x91, // Keyboard LANG2
    Lang3          = 0x92, // Keyboard LANG3
    Lang4          = 0x93, // Keyboard LANG4
    Lang5          = 0x94, // Keyboard LANG5
    Lang6          = 0x95, // Keyboard LANG6
    Lang7          = 0x96, // Keyboard LANG7
    Lang8          = 0x97, // Keyboard LANG8
    Lang9          = 0x98, // Keyboard LANG9
    AltErase       = 0x99, // Keyboard Alternate Erase
    SysReq         = 0x9a, // Keyboard SysReq/Attention
    Cancel         = 0x9b, // Keyboard Cancel
    Clear          = 0x9c, // Keyboard Clear
    Prior          = 0x9d, // Keyboard Prior
    Return         = 0x9e, // Keyboard Return
    Separator      = 0x9f, // Keyboard Separator
    Out            = 0xa0, // Keyboard Out
    Oper           = 0xa1, // Keyboard Oper
    ClearAgain     = 0xa2, // Keyboard Clear/Again
    CrSel          = 0xa3, // Keyboard CrSel/Props
    ExSel          = 0xa4, // Keyboard ExSel
    LCtrl          = 0xe0, // Keyboard LeftControl
    LShift         = 0xe1, // Keyboard LeftShift
    LAlt           = 0xe2, // Keyboard LeftAlt
    LGui           = 0xe3, // Keyboard Left GUI
    RCtrl          = 0xe4, // Keyboard RightControl
    RShift         = 0xe5, // Keyboard RightShift
    RAlt           = 0xe6, // Keyboard RightAlt
    RGui           = 0xe7  // Keyboard Right GUI
};

namespace KeyCodes
{

constexpr uint8_t ModifierOffset = 0xe0;

StrRef keyName(KeyCode key);
KeyCode keyCode(const StrRef& keyName);

}

#endif
