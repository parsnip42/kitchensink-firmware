#include "keymap.h"

#include <array>

namespace KeyMap
{

namespace
{

const std::array<Entry, 0xff> tableData{{
        { },
        { },
        { },
        { },
        { 'a', 'A' },
        { 'b', 'B' },
        { 'c', 'C' },
        { 'd', 'D' },
        { 'e', 'E' },
        { 'f', 'F' },
        { 'g', 'G' },
        { 'h', 'H' },
        { 'i', 'I' },
        { 'j', 'J' },
        { 'k', 'K' },
        { 'l', 'L' },
        { 'm', 'M' },
        { 'n', 'N' },
        { 'o', 'O' },
        { 'p', 'P' },
        { 'q', 'Q' },
        { 'r', 'R' },
        { 's', 'S' },
        { 't', 'T' },
        { 'u', 'U' },
        { 'v', 'V' },
        { 'w', 'W' },
        { 'x', 'X' },
        { 'y', 'Y' },
        { 'z', 'Z' },
        { '1', '!' },
        { '2', '"' },
        { '3', '?' },
        { '4', '$' },
        { '5', '%' },
        { '6', '^' },
        { '7', '&' },
        { '8', '*' },
        { '9', '(' },
        { '0', ')' },
        {  },
        {  },
        {  },
        {  },
        { ' ', ' ' },
        { '-', '_' },
        { '=', '+' },
        { '[', '{' },
        { ']', '}' },
        { '\\', '|' },
        { '#', '~' },
        { ';', ':' },
        { '\'', '@' },
        { '`' },
        { ',', '<' },
        { '.', '>' },
        { '/', '?' }
}};

}

const Entry& getEntry(KeyCode key)
{
    return tableData[static_cast<size_t>(key)];
}

}
