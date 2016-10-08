#include "keymap.h"

namespace KeyMap
{

Entry::Entry()
    : dflt("?")
    , shift("?")
{ }

Entry::Entry(const char* nDflt,
             const char* nShift)
    : dflt(nDflt)
    , shift(nShift)
{ }

namespace
{

std::array<Entry, 0xff> tableData{
    Entry(),
    Entry(),
    Entry(),
    Entry(),
    Entry("a", "A"),
    Entry("b", "B"),
    Entry("c", "C"),
    Entry("d", "D"),
    Entry("e", "E"),
    Entry("f", "F"),
    Entry("g", "G"),
    Entry("h", "H"),
    Entry("i", "I"),
    Entry("j", "J"),
    Entry("k", "K"),
    Entry("l", "L"),
    Entry("m", "M"),
    Entry("n", "N"),
    Entry("o", "O"),
    Entry("p", "P"),
    Entry("q", "Q"),
    Entry("r", "R"),
    Entry("s", "S"),
    Entry("t", "T"),
    Entry("u", "U"),
    Entry("v", "V"),
    Entry("w", "W"),
    Entry("x", "X"),
    Entry("y", "Y"),
    Entry("z", "Z"),
    Entry("1", "!"),
    Entry("2", "\""),
    Entry("3", "£"),
    Entry("4", "$"),
    Entry("5", "%"),
    Entry("6", "^"),
    Entry("7", "&"),
    Entry("8", "*"),
    Entry("9", "("),
    Entry("0", ")"),
    Entry(),
    Entry(),
    Entry(),
    Entry(),
    Entry(" ", " "),
    Entry("-", "_"),
    Entry("=", "+"),
    Entry("[", "{"),
    Entry("]", "}")
};

}

const std::array<Entry, 0xff>& table()
{
    return tableData;
}

}
