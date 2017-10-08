#!/usr/bin/python

import sys

def dump_raw(arr):
    for elem in arr:
        print "{:08b}".format(elem)

def read_raw(f):
    raw = []
    
    for line in f:
        line = line.rstrip('\n')
        
        if line == 'ENDCHAR':
            break

        raw.append(int(line, 16))
        
    return raw
        
def main(argv):
    
    if len(argv) != 4:
        print "Syntax: " + argv[0] + " <bdf file> <h file> <cpp file>"
        return 1

    bdf_file = argv[1]
    h_file = argv[2]
    cpp_file = argv[3]
    
    width = 0
    height = 0
    data = {}
    
    with open(bdf_file) as f:
        for line in f:
            line = line.rstrip('\n')

            if line.startswith('FONTBOUNDINGBOX'):
                tokens = line.split(' ')
                width = int(tokens[1])
                height = int(tokens[2])
            elif line.startswith('STARTCHAR'):
                current = line[10:]
            elif line == 'BITMAP':
                data[current] = read_raw(f)

    array = []

    glyphs = [
        'exclam','quotedbl','numbersign','dollar','percent','ampersand','quotesingle','parenleft','parenright','asterisk',
        'plus','comma','hyphen','period','slash','zero','one','two','three','four',
        'five','six','seven','eight','nine','colon','semicolon','less','equal','greater',
        'question','at', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
        'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
        'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'bracketleft', 'backslash',
        'bracketright', 'asciicircum', 'underscore', 'grave', 'a', 'b', 'c', 'd', 'e', 'f',
        'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
        'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
        'braceleft', 'bar', 'braceright', 'asciitilde', 'uni2714'
    ]
    
    for y in range(0, height):
        for glyph in glyphs:
            try:
                array.append('0x{:02x}'.format(data[glyph][y]))
            except:
                array.append('0x{:02x}'.format(0))

    with open(h_file, 'w') as f:
        f.write('''\
#ifndef INCLUDED_FONT_H
#define INCLUDED_FONT_H

#include "types/strref.h"
#include <cstdint>

namespace Font
{

constexpr int kWidth     = ''' + str(width) + ''';
constexpr int kHeight    = ''' + str(height) + ''';
constexpr int kBpp       = 1;
constexpr int kCharCount = ''' + str(len(glyphs)) + ''';

extern const uint8_t fontData[];

inline
constexpr int width(const StrRef& text)
{
    return text.length() * kWidth;
}

}

#endif
''')
    
    with open(cpp_file, 'w') as f:
        f.write('''\
#include "ui/font.h"

#include <cstdint>

namespace Font
{

const uint8_t fontData[] =
{
''')
        
        for i in range(0, len(array), 20):
            f.write('    ' + ','.join(array[i:i + 20]) + ',\n')
        
        f.write('''\
};

}
''')
        
    return 0;

if __name__ == '__main__':
    sys.exit(main(sys.argv))
