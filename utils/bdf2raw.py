#!/usr/bin/python

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
        
def main():
    data = {}
    
    with open('ter-u12n.bdf') as f:
        for line in f:
            line = line.rstrip('\n')
            
            if line.startswith('STARTCHAR'):
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
    
    for y in range(0, 12):
        for glyph in glyphs:
            try:
                array.append('0x{:02x}'.format(data[glyph][y]))
            except:
                array.append('0x{:02x}'.format(0))
                
    print 'constexpr uint8_t charset[] ='
    print '{'
    
    for i in range(0, len(array), 20):
        print '    ' + ','.join(array[i:i + 20]) + ','
        
    print '};\n'
    print 'constexpr int kCharsetCount = ' + str(len(glyphs)) + ';\n'

            

if __name__ == '__main__':
    main()
