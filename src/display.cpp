#include "display.h"

#include "Wire.h"

#include <stdio.h>
#include <inttypes.h>

namespace
{

const int ledPin = 13;
const int db[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
const size_t db_count = sizeof(db)/sizeof(*db);
const int dc = 21;
const int reset = 22;
const int csrw = 23;

void writeBus(unsigned char data, int type)
{
    digitalWrite(dc, type);
    digitalWrite(csrw, 0);

    for (size_t i = 0; i < db_count; ++i)
    {
        digitalWrite(db[i], (data >> i) & 1);
    }
 
    digitalWrite(csrw, 1);
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
    {
        writeData(0x00);
    }
}

void Display::writeInst(unsigned char data)
{
    writeBus(data, 0);
}

void Display::writeData(unsigned char data)
{
    writeBus(data, 1);
}

void Display::initRegion(int x, int y, int w, int h)
{
    writeInst(0x15);
    writeData(x);
    writeData(x + (w >> 2) -1);

    writeInst(0x75);
    writeData(y);
    writeData(y + h - 1);

    writeInst(0x5C);
}

