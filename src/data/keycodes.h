#ifndef INCLUDED_KEYCODES_H
#define INCLUDED_KEYCODES_H

#include "types/strref.h"

#include <cstdint>

typedef uint8_t keycode_t;

namespace KeyCodes
{
constexpr keycode_t None           = 0x00; // Reserved (no event indicated)
constexpr keycode_t ErrorRollOver  = 0x01; // Keyboard ErrorRollOver
constexpr keycode_t PostFail       = 0x02; // Keyboard POSTFail
constexpr keycode_t ErrorUndefined = 0x03; // Keyboard ErrorUndefined
constexpr keycode_t A              = 0x04; // Keyboard a and A
constexpr keycode_t B              = 0x05; // Keyboard b and B
constexpr keycode_t C              = 0x06; // Keyboard c and C
constexpr keycode_t D              = 0x07; // Keyboard d and D
constexpr keycode_t E              = 0x08; // Keyboard e and E
constexpr keycode_t F              = 0x09; // Keyboard f and F
constexpr keycode_t G              = 0x0a; // Keyboard g and G
constexpr keycode_t H              = 0x0b; // Keyboard h and H
constexpr keycode_t I              = 0x0c; // Keyboard i and I
constexpr keycode_t J              = 0x0d; // Keyboard j and J
constexpr keycode_t K              = 0x0e; // Keyboard k and K
constexpr keycode_t L              = 0x0f; // Keyboard l and L
constexpr keycode_t M              = 0x10; // Keyboard m and M
constexpr keycode_t N              = 0x11; // Keyboard n and N
constexpr keycode_t O              = 0x12; // Keyboard o and O
constexpr keycode_t P              = 0x13; // Keyboard p and P
constexpr keycode_t Q              = 0x14; // Keyboard q and Q
constexpr keycode_t R              = 0x15; // Keyboard r and R
constexpr keycode_t S              = 0x16; // Keyboard s and S
constexpr keycode_t T              = 0x17; // Keyboard t and T
constexpr keycode_t U              = 0x18; // Keyboard u and U
constexpr keycode_t V              = 0x19; // Keyboard v and V
constexpr keycode_t W              = 0x1a; // Keyboard w and W
constexpr keycode_t X              = 0x1b; // Keyboard x and X
constexpr keycode_t Y              = 0x1c; // Keyboard y and Y
constexpr keycode_t Z              = 0x1d; // Keyboard z and Z
constexpr keycode_t K1             = 0x1e; // Keyboard 1 and !
constexpr keycode_t K2             = 0x1f; // Keyboard 2 and @
constexpr keycode_t K3             = 0x20; // Keyboard 3 and #
constexpr keycode_t K4             = 0x21; // Keyboard 4 and $
constexpr keycode_t K5             = 0x22; // Keyboard 5 and %
constexpr keycode_t K6             = 0x23; // Keyboard 6 and ^
constexpr keycode_t K7             = 0x24; // Keyboard 7 and &
constexpr keycode_t K8             = 0x25; // Keyboard 8 and *
constexpr keycode_t K9             = 0x26; // Keyboard 9 and (
constexpr keycode_t K0             = 0x27; // Keyboard 0 and )
constexpr keycode_t Enter          = 0x28; // Keyboard Return (ENTER)
constexpr keycode_t Esc            = 0x29; // Keyboard ESCAPE
constexpr keycode_t Backspace      = 0x2a; // Keyboard DELETE (Backspace)
constexpr keycode_t Tab            = 0x2b; // Keyboard Tab
constexpr keycode_t Space          = 0x2c; // Keyboard Spacebar
constexpr keycode_t Minus          = 0x2d; // Keyboard - and (underscore)
constexpr keycode_t Equal          = 0x2e; // Keyboard = and +
constexpr keycode_t LBrace         = 0x2f; // Keyboard [ and {
constexpr keycode_t RBrace         = 0x30; // Keyboard ] and }
constexpr keycode_t Backslash      = 0x31; // Keyboard \ and |
constexpr keycode_t NonUsHash      = 0x32; // Keyboard Non-US # and ~
constexpr keycode_t Semicolon      = 0x33; // Keyboard ; and :
constexpr keycode_t Quote          = 0x34; // Keyboard ' and "
constexpr keycode_t Grave          = 0x35; // Keyboard Grave Accent and Tilde
constexpr keycode_t Comma          = 0x36; // Keyboard , and <
constexpr keycode_t Dot            = 0x37; // Keyboard . and >
constexpr keycode_t Slash          = 0x38; // Keyboard / and ?
constexpr keycode_t CapsLock       = 0x39; // Keyboard Caps Lock
constexpr keycode_t F1             = 0x3a; // Keyboard F1
constexpr keycode_t F2             = 0x3b; // Keyboard F2
constexpr keycode_t F3             = 0x3c; // Keyboard F3
constexpr keycode_t F4             = 0x3d; // Keyboard F4
constexpr keycode_t F5             = 0x3e; // Keyboard F5
constexpr keycode_t F6             = 0x3f; // Keyboard F6
constexpr keycode_t F7             = 0x40; // Keyboard F7
constexpr keycode_t F8             = 0x41; // Keyboard F8
constexpr keycode_t F9             = 0x42; // Keyboard F9
constexpr keycode_t F10            = 0x43; // Keyboard F10
constexpr keycode_t F11            = 0x44; // Keyboard F11
constexpr keycode_t F12            = 0x45; // Keyboard F12
constexpr keycode_t PrintScreen    = 0x46; // Keyboard PrintScreen
constexpr keycode_t ScrollLock     = 0x47; // Keyboard Scroll Lock
constexpr keycode_t Pause          = 0x48; // Keyboard Pause
constexpr keycode_t Insert         = 0x49; // Keyboard Insert
constexpr keycode_t Home           = 0x4a; // Keyboard Home
constexpr keycode_t PageUp         = 0x4b; // Keyboard PageUp
constexpr keycode_t Delete         = 0x4c; // Keyboard Delete Forward
constexpr keycode_t End            = 0x4d; // Keyboard End
constexpr keycode_t PageDown       = 0x4e; // Keyboard PageDown
constexpr keycode_t Right          = 0x4f; // Keyboard RightArrow
constexpr keycode_t Left           = 0x50; // Keyboard LeftArrow
constexpr keycode_t Down           = 0x51; // Keyboard DownArrow
constexpr keycode_t Up             = 0x52; // Keyboard UpArrow
constexpr keycode_t NumLock        = 0x53; // Keypad Num Lock and Clear
constexpr keycode_t KpSlash        = 0x54; // Keypad /
constexpr keycode_t KpAsterisk     = 0x55; // Keypad *
constexpr keycode_t KpMinus        = 0x56; // Keypad -
constexpr keycode_t KpPlus         = 0x57; // Keypad +
constexpr keycode_t KpEnter        = 0x58; // Keypad ENTER
constexpr keycode_t Kp1            = 0x59; // Keypad 1 and End
constexpr keycode_t Kp2            = 0x5a; // Keypad 2 and Down Arrow
constexpr keycode_t Kp3            = 0x5b; // Keypad 3 and PageDn
constexpr keycode_t Kp4            = 0x5c; // Keypad 4 and Left Arrow
constexpr keycode_t Kp5            = 0x5d; // Keypad 5
constexpr keycode_t Kp6            = 0x5e; // Keypad 6 and Right Arrow
constexpr keycode_t Kp7            = 0x5f; // Keypad 7 and Home
constexpr keycode_t Kp8            = 0x60; // Keypad 8 and Up Arrow
constexpr keycode_t Kp9            = 0x61; // Keypad 9 and PageUp
constexpr keycode_t Kp0            = 0x62; // Keypad 0 and Insert
constexpr keycode_t KpDot          = 0x63; // Keypad . and Delete
constexpr keycode_t NonUsBackslash = 0x64; // Keyboard Non-US \ and |
constexpr keycode_t Application    = 0x65; // Keyboard Application
constexpr keycode_t Power          = 0x66; // Keyboard Power
constexpr keycode_t KpEqual        = 0x67; // Keypad =
constexpr keycode_t F13            = 0x68; // Keyboard F13
constexpr keycode_t F14            = 0x69; // Keyboard F14
constexpr keycode_t F15            = 0x6a; // Keyboard F15
constexpr keycode_t F16            = 0x6b; // Keyboard F16
constexpr keycode_t F17            = 0x6c; // Keyboard F17
constexpr keycode_t F18            = 0x6d; // Keyboard F18
constexpr keycode_t F19            = 0x6e; // Keyboard F19
constexpr keycode_t F20            = 0x6f; // Keyboard F20
constexpr keycode_t F21            = 0x70; // Keyboard F21
constexpr keycode_t F22            = 0x71; // Keyboard F22
constexpr keycode_t F23            = 0x72; // Keyboard F23
constexpr keycode_t F24            = 0x73; // Keyboard F24
constexpr keycode_t Execute        = 0x74; // Keyboard Execute
constexpr keycode_t Help           = 0x75; // Keyboard Help
constexpr keycode_t Menu           = 0x76; // Keyboard Menu
constexpr keycode_t Select         = 0x77; // Keyboard Select
constexpr keycode_t Stop           = 0x78; // Keyboard Stop
constexpr keycode_t Again          = 0x79; // Keyboard Again
constexpr keycode_t Undo           = 0x7a; // Keyboard Undo
constexpr keycode_t Cut            = 0x7b; // Keyboard Cut
constexpr keycode_t Copy           = 0x7c; // Keyboard Copy
constexpr keycode_t Paste          = 0x7d; // Keyboard Paste
constexpr keycode_t Find           = 0x7e; // Keyboard Find
constexpr keycode_t Mute           = 0x7f; // Keyboard Mute
constexpr keycode_t VolumeUp       = 0x80; // Keyboard Volume Up
constexpr keycode_t VolumeDown     = 0x81; // Keyboard Volume Down
constexpr keycode_t LockCapsLock   = 0x82; // Keyboard Locking Caps Lock
constexpr keycode_t LockNumLock    = 0x83; // Keyboard Locking Num Lock
constexpr keycode_t LockScrollLock = 0x84; // Keyboard Locking Scroll Lock
constexpr keycode_t KpComma        = 0x85; // Keypad Comma
constexpr keycode_t KpEqualSign    = 0x86; // Keypad Equal Sign
constexpr keycode_t International1 = 0x87; // Keyboard International1
constexpr keycode_t International2 = 0x88; // Keyboard International2
constexpr keycode_t International3 = 0x89; // Keyboard International3
constexpr keycode_t International4 = 0x8a; // Keyboard International4
constexpr keycode_t International5 = 0x8b; // Keyboard International5
constexpr keycode_t International6 = 0x8c; // Keyboard International6
constexpr keycode_t International7 = 0x8d; // Keyboard International7
constexpr keycode_t International8 = 0x8e; // Keyboard International8
constexpr keycode_t International9 = 0x8f; // Keyboard International9
constexpr keycode_t Lang1          = 0x90; // Keyboard LANG1
constexpr keycode_t Lang2          = 0x91; // Keyboard LANG2
constexpr keycode_t Lang3          = 0x92; // Keyboard LANG3
constexpr keycode_t Lang4          = 0x93; // Keyboard LANG4
constexpr keycode_t Lang5          = 0x94; // Keyboard LANG5
constexpr keycode_t Lang6          = 0x95; // Keyboard LANG6
constexpr keycode_t Lang7          = 0x96; // Keyboard LANG7
constexpr keycode_t Lang8          = 0x97; // Keyboard LANG8
constexpr keycode_t Lang9          = 0x98; // Keyboard LANG9
constexpr keycode_t AltErase       = 0x99; // Keyboard Alternate Erase
constexpr keycode_t SysReq         = 0x9a; // Keyboard SysReq/Attention
constexpr keycode_t Cancel         = 0x9b; // Keyboard Cancel
constexpr keycode_t Clear          = 0x9c; // Keyboard Clear
constexpr keycode_t Prior          = 0x9d; // Keyboard Prior
constexpr keycode_t Return         = 0x9e; // Keyboard Return
constexpr keycode_t Separator      = 0x9f; // Keyboard Separator
constexpr keycode_t Out            = 0xa0; // Keyboard Out
constexpr keycode_t Oper           = 0xa1; // Keyboard Oper
constexpr keycode_t ClearAgain     = 0xa2; // Keyboard Clear/Again
constexpr keycode_t CrSel          = 0xa3; // Keyboard CrSel/Props
constexpr keycode_t ExSel          = 0xa4; // Keyboard ExSel
constexpr keycode_t LCtrl          = 0xe0; // Keyboard LeftControl
constexpr keycode_t LShift         = 0xe1; // Keyboard LeftShift
constexpr keycode_t LAlt           = 0xe2; // Keyboard LeftAlt
constexpr keycode_t LGui           = 0xe3; // Keyboard Left GUI
constexpr keycode_t RCtrl          = 0xe4; // Keyboard RightControl
constexpr keycode_t RShift         = 0xe5; // Keyboard RightShift
constexpr keycode_t RAlt           = 0xe6; // Keyboard RightAlt
constexpr keycode_t RGui           = 0xe7; // Keyboard Right GUI

constexpr keycode_t ModifierOffset = 0xe0;

StrRef keyName(keycode_t keyCode);
keycode_t keyCode(const StrRef& keyName);

};

#endif
