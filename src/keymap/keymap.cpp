#include "keymap.h"

namespace KeyMap
{

namespace
{

const std::array<Entry, 0xff> tableData{{
    Entry(),
    Entry(),
    Entry(),
    Entry(),
    Entry("A",      'a', 'A'),
    Entry("B",      'b', 'B'),
    Entry("C",      'c', 'C'),
    Entry("D",      'd', 'D'),
    Entry("E",      'e', 'E'),
    Entry("F",      'f', 'F'),
    Entry("G",      'g', 'G'),
    Entry("H",      'h', 'H'),
    Entry("I",      'i', 'I'),
    Entry("J",      'j', 'J'),
    Entry("K",      'k', 'K'),
    Entry("L",      'l', 'L'),
    Entry("M",      'm', 'M'),
    Entry("N",      'n', 'N'),
    Entry("O",      'o', 'O'),
    Entry("P",      'p', 'P'),
    Entry("Q",      'q', 'Q'),
    Entry("R",      'r', 'R'),
    Entry("S",      's', 'S'),
    Entry("T",      't', 'T'),
    Entry("U",      'u', 'U'),
    Entry("V",      'v', 'V'),
    Entry("W",      'w', 'W'),
    Entry("X",      'x', 'X'),
    Entry("Y",      'y', 'Y'),
    Entry("Z",      'z', 'Z'),
    Entry("1",      '1', '!'),
    Entry("2",      '2', '"'),
    Entry("3",      '3', '?'),
    Entry("4",      '4', '$'),
    Entry("5",      '5', '%'),
    Entry("6",      '6', '^'),
    Entry("7",      '7', '&'),
    Entry("8",      '8', '*'),
    Entry("9",      '9', '('),
    Entry("0",      '0', ')'),
    Entry("Enter"   ),
    Entry("Esc"     ),
    Entry("Backspc" ),
    Entry("Tab"     ),
    Entry("Space",  ' ', ' '),
    Entry("Minus",  '-', '_'),
    Entry("Equal",  '=', '+'),
    Entry("LBrace", '[', '{'),
    Entry("RBrace", ']', '}')
}};

}

const Entry& getEntry(uint8_t n)
{
    return tableData[n];
}

const Entry* getEntry(const Types::StrRef& name)
{
    for (const auto& entry : tableData)
    {
        if (entry.name == name)
        {
            return &entry;
        }
    }

    return 0;
}

}
