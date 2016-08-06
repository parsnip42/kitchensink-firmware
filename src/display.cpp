#include "display.h"

#include "Wire.h"

#include <stdio.h>
#include <inttypes.h>

namespace
{

const unsigned char charset[] = {
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 36, 0, 8, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 70, 8, 36, 36, 8, 38, 24, 8, 16, 4, 0, 0, 0, 0, 0, 32, 60, 16, 60, 60, 64, 126, 56, 126, 60, 60, 0, 0, 0, 0, 0, 60, 62, 60, 62, 60, 30, 126, 126, 60, 66, 28, 112, 66, 2, 65, 66, 60, 62, 60, 62, 60, 127, 66, 66, 65, 66, 65, 126, 28, 2, 28, 20, 0, 0, 0, 2, 0, 64, 0, 112, 0, 2, 8, 32, 2, 12, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 48, 8, 12, 73, 8, 36, 36, 62, 41, 36, 8, 8, 8, 0, 0, 0, 0, 0, 32, 66, 24, 66, 66, 96, 2, 4, 64, 66, 66, 0, 0, 32, 0, 2, 66, 65, 66, 66, 66, 34, 2, 2, 66, 66, 8, 32, 34, 2, 99, 66, 66, 66, 66, 66, 66, 8, 66, 66, 65, 66, 65, 64, 4, 2, 16, 34, 0, 0, 0, 2, 0, 64, 0, 8, 0, 2, 8, 32, 2, 8, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 8, 8, 16, 49, 8, 0, 36, 73, 22, 36, 0, 4, 16, 0, 0, 0, 0, 0, 16, 66, 20, 66, 66, 80, 2, 2, 64, 66, 66, 0, 0, 16, 0, 4, 66, 121, 66, 66, 66, 66, 2, 2, 66, 66, 8, 32, 18, 2, 85, 66, 66, 66, 66, 66, 2, 8, 66, 66, 65, 36, 34, 64, 4, 4, 16, 0, 0, 0, 0, 2, 0, 64, 0, 8, 0, 2, 0, 0, 2, 8, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 8, 8, 16, 0, 8, 0, 126, 9, 16, 24, 0, 4, 16, 36, 8, 0, 0, 0, 16, 98, 16, 64, 64, 72, 2, 2, 32, 66, 66, 8, 8, 8, 126, 8, 66, 69, 66, 66, 2, 66, 2, 2, 2, 66, 8, 32, 10, 2, 73, 70, 66, 66, 66, 66, 2, 8, 66, 66, 65, 36, 34, 32, 4, 4, 16, 0, 0, 0, 60, 62, 60, 124, 60, 62, 124, 62, 12, 48, 66, 8, 63, 62, 60, 62, 124, 122, 124, 62, 66, 66, 65, 66, 66, 126, 8, 8, 16, 0, 8, 0, 36, 9, 8, 12, 0, 4, 16, 24, 8, 0, 0, 0, 8, 82, 16, 32, 56, 68, 62, 62, 32, 60, 66, 8, 8, 4, 0, 16, 32, 69, 66, 62, 2, 66, 30, 30, 2, 126, 8, 32, 6, 2, 73, 74, 66, 66, 66, 66, 60, 8, 66, 66, 65, 24, 20, 16, 4, 8, 16, 0, 0, 0, 64, 66, 66, 66, 66, 8, 66, 66, 8, 32, 34, 8, 73, 66, 66, 66, 66, 6, 2, 8, 66, 66, 65, 66, 66, 32, 4, 8, 32, 0, 8, 0, 36, 62, 8, 82, 0, 4, 16, 126, 62, 0, 126, 0, 8, 74, 16, 16, 64, 66, 64, 66, 16, 66, 124, 0, 0, 2, 0, 32, 16, 69, 126, 66, 2, 66, 2, 2, 114, 66, 8, 32, 6, 2, 65, 82, 66, 62, 66, 62, 64, 8, 66, 36, 73, 24, 8, 8, 4, 8, 16, 0, 0, 0, 124, 66, 2, 66, 66, 8, 66, 66, 8, 32, 18, 8, 73, 66, 66, 66, 66, 2, 2, 8, 66, 66, 73, 36, 66, 16, 8, 8, 16, 0, 8, 0, 126, 72, 4, 34, 0, 4, 16, 24, 8, 0, 0, 0, 4, 70, 16, 8, 64, 126, 64, 66, 16, 66, 64, 0, 0, 4, 126, 16, 16, 101, 66, 66, 2, 66, 2, 2, 66, 66, 8, 32, 10, 2, 65, 98, 66, 2, 66, 10, 64, 8, 66, 36, 73, 36, 8, 4, 4, 16, 16, 0, 0, 0, 66, 66, 2, 66, 126, 8, 66, 66, 8, 32, 14, 8, 73, 66, 66, 66, 66, 2, 60, 8, 66, 36, 73, 24, 66, 8, 8, 8, 16, 0, 0, 0, 36, 72, 52, 34, 0, 4, 16, 36, 8, 0, 0, 0, 4, 66, 16, 4, 66, 64, 64, 66, 8, 66, 64, 0, 0, 8, 0, 8, 0, 89, 66, 66, 66, 66, 2, 2, 66, 66, 8, 34, 18, 2, 65, 66, 66, 2, 66, 18, 66, 8, 66, 36, 85, 36, 8, 2, 4, 16, 16, 0, 0, 0, 66, 66, 2, 66, 2, 8, 66, 66, 8, 32, 18, 8, 73, 66, 66, 66, 66, 2, 64, 8, 66, 36, 73, 36, 66, 4, 8, 8, 16, 0, 8, 0, 36, 73, 74, 34, 0, 8, 8, 0, 0, 8, 0, 8, 2, 66, 16, 2, 66, 64, 66, 66, 8, 66, 32, 8, 8, 16, 0, 4, 16, 1, 66, 66, 66, 34, 2, 2, 66, 66, 8, 34, 34, 2, 65, 66, 66, 2, 82, 34, 66, 8, 66, 24, 99, 66, 8, 2, 4, 32, 16, 0, 0, 0, 66, 66, 66, 66, 2, 8, 66, 66, 8, 32, 34, 8, 73, 66, 66, 66, 66, 2, 64, 8, 66, 24, 73, 66, 66, 2, 8, 8, 16, 0, 8, 0, 36, 62, 50, 92, 0, 16, 4, 0, 0, 8, 0, 8, 2, 60, 124, 126, 60, 64, 60, 60, 8, 60, 28, 8, 8, 32, 0, 2, 16, 126, 66, 62, 60, 30, 126, 2, 60, 66, 28, 28, 66, 126, 65, 66, 60, 2, 60, 66, 60, 8, 60, 24, 65, 66, 8, 126, 28, 32, 28, 0, 0, 0, 124, 62, 60, 124, 60, 8, 124, 66, 28, 34, 66, 28, 73, 66, 60, 62, 124, 2, 62, 112, 124, 24, 62, 66, 124, 126, 48, 8, 12, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 126, 0, 0, 0, 0, 0, 0, 0, 64, 0, 0, 34, 0, 0, 0, 0, 0, 2, 64, 0, 0, 0, 0, 0, 0, 0, 64, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 60, 0, 0, 28, 0, 0, 0, 0, 0, 2, 64, 0, 0, 0, 0, 0, 0, 0, 60, 0, 0, 0, 0, 0
};


const int ledPin = 13;
const int db[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
const size_t db_count = sizeof(db)/sizeof(*db);
const int dc = 23;
const int reset = 22;
const int csrw = 21;

void writeBus(unsigned char data, int type)
{
    digitalWrite(dc, type);
    digitalWrite(csrw, 0);

    for (size_t i = 0; i < db_count; i++)
    {
        digitalWrite(db[i], (data >> i) & 1);
    }
    // delay(2);
 
    digitalWrite(csrw, 1);
}

void writeInst(unsigned char data)
{
    writeBus(data, 0);
}

void writeData(unsigned char data)
{
    writeBus(data, 1);
}

}

Display::Display()
{ }

void Display::init()
{
    for (size_t i = 0; i < db_count; i++)
    {
        pinMode(db[i], OUTPUT);
    }

    pinMode(dc, OUTPUT);
    pinMode(reset, OUTPUT);
    pinMode(csrw, OUTPUT);

    digitalWrite(reset, HIGH);
    delay(200);
    digitalWrite(reset, LOW);
    delay(200);
    digitalWrite(reset, HIGH);

    writeInst(0xFD); /*SET COMMAND LOCK */
    writeData(0x12); /* UNLOCK */
    writeInst(0xAE); /*DISPLAY OFF*/
    writeInst(0xB3); /*DISPLAYDIVIDE CLOCKRADIO/OSCILLATAR FREQUANCY*/
    writeData(0x91); /*multiplex ratio*/
    writeData(0x3F); /*duty = 1/64*/
    writeInst(0xA2); /*set offset*/
    writeData(0x00);
    writeInst(0xA1); /*start line*/
    writeData(0x00);
    writeInst(0xA0); /*set remap*/
    writeData(0x14); writeData(0x11);
    //writeData(0x0); writeData(0x0);

    writeInst(0xAB); /*funtion selection*/
    writeData(0x01); /* selection external vdd */
    writeInst(0xB4);
    writeData(0xA0); writeData(0xFD);
    writeInst(0xC1); /*set contrast current */

    writeData(0x7f);

    writeInst(0xC7); /*master contrast current control*/
    writeData(0x0F);
    writeInst(0xB1); /*SET PHASE LENGTH*/
    writeData(0xE2);
    writeInst(0xD1);
    writeData(0x82); writeData(0x20);
    writeInst(0xBB); /*SET PRE-CHANGE VOLTAGE*/
    writeData(0x1F);
    writeInst(0xB6); /*SET SECOND PRE-CHARGE PERIOD*/
    writeData(0x08);
    writeInst(0xBE); /* SET VCOMH */
    writeData(0x07);

    writeInst(0xb9); /* linear gray scale */

    writeInst(0x5C);
    for (int i=0;i<240*64*2;i++)
        writeData(0x00);

    writeInst(0xA6);
    writeInst(0xAF); /*display ON*/
}

void Display::paint(int x, int y, const char* str)
{
    int len = strlen(str);
    int charHeight = 14;
    //int charWidth = 8;

    // Column start-end (0,119)
    writeInst(0x15);
    writeData(x);
    writeData(x+(len*2)-1);

    // Row start-end (0,127)
    writeInst(0x75);
    writeData(y);
    writeData(y+charHeight);

    writeInst(0x5C);

    for (int y=0;y<charHeight;y++)
    {
        for (int x=0;x<len;x++)
        {
            unsigned char a0=0;
            unsigned char a1=0;
            unsigned char a2=0;
            unsigned char a3=0;                

            if (str[x] > 32 && str[x] < 127)
            {
                unsigned char c = charset[str[x]-33 + (y*94)];
                
                a0=(((c>>7) & 1) ? 0xf : 0x00) | ((c>>6 & 1) ? 0xf0 : 0x00);
                a1=(((c>>5) & 1) ? 0xf : 0x00) | ((c>>4 & 1) ? 0xf0 : 0x00);
                a2=(((c>>3) & 1) ? 0xf : 0x00) | ((c>>2 & 1) ? 0xf0 : 0x00);
                a3=(((c>>1) & 1) ? 0xf : 0x00) | ((c & 1) ?    0xf0 : 0x00);
            }

            writeData(a3);
            writeData(a2);
            writeData(a1);
            writeData(a0);
        }
    }
}

void Display::clear()
{
    writeInst(0x15);
    writeData(0);
    writeData(119);
    
    writeInst(0x75);
    writeData(0);
    writeData(127);
    
    writeInst(0x5C);

    for (int i=0;i<240*64*2;i++)
        writeData(0x00);
}
