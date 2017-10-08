#include "hardware/dmoled32display.h"

#include <Wire.h>
#include <core_pins.h>

namespace
{

const int ledPin = 13;
const int db[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
const size_t db_count = sizeof(db)/sizeof(*db);
const int dc = 21;
const int reset = 22;
const int csrw = 23;

inline void writeByte(uint8_t data, int type) __attribute__((always_inline, unused));
inline void writeByte(uint8_t data, int type)
{
    digitalWriteFast(21, type);
    digitalWriteFast(23, 0);

#if defined(__MK20DX128__) || defined(__MK20DX256__)

    static uint8_t lastData(0);
    
    uint8_t toggle(data ^ lastData);

    GPIOA_PTOR = ((toggle >> 3) & 0x3) << 12;
    GPIOB_PTOR = (toggle & 0x3) << 16;
    GPIOD_PTOR = (((toggle >> 2) & 1) |
                  (((toggle >> 5) & 1) << 7) |
                  (((toggle >> 6) & 1) << 4) |
                  (((toggle >> 7) & 1) << 2));

    lastData = data;
    
#else
        
    digitalWriteFast(0, data & 1);
    digitalWriteFast(1, (data >> 1) & 1);
    digitalWriteFast(2, (data >> 2) & 1);
    digitalWriteFast(3, (data >> 3) & 1);
    digitalWriteFast(4, (data >> 4) & 1);
    digitalWriteFast(5, (data >> 5) & 1);
    digitalWriteFast(6, (data >> 6) & 1);
    digitalWriteFast(7, (data >> 7) & 1);
    
#endif
    
    digitalWriteFast(23, 1);
}

}

DMOLED32Display::DMOLED32Display()
{ }

void DMOLED32Display::init()
{
    for (size_t i = 0; i < db_count; i++)
    {
        pinMode(db[i], OUTPUT);
    }

    pinMode(dc, OUTPUT);
    pinMode(reset, OUTPUT);
    pinMode(csrw, OUTPUT);

    digitalWriteFast(reset, HIGH);
    delay(200);
    digitalWriteFast(reset, LOW);
    delay(200);
    digitalWriteFast(reset, HIGH);

    writeInst(0xFD); /*SET COMMAND LOCK */
    writeData(0x12); /* UNLOCK */
    writeInst(0xAE); /*DISPLAY OFF*/
    writeInst(0xB3); /*DISPLAYDIVIDE CLOCKRADIO/OSCILLATAR FREQUANCY*/
    writeData(0x91); /*multiplex ratio*/
    writeInst(0xCA);
    writeData(0x3F); /*duty = 1/64*/
    writeInst(0xA2); /*set offset*/
    writeData(0x00);
    writeInst(0xA1); /*start line*/
    writeData(0x00);

    writeInst(0xA0); /*set remap*/
    writeData(0x14); writeData(0x11);

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

void DMOLED32Display::clear()
{
    writeInst(0x15);
    writeData(0);
    writeData(119);
    
    writeInst(0x75);
    writeData(0);
    writeData(127);
    
    writeInst(0x5C);

    for (int i = 0;i < 240 * 64 * 2; ++i)
    {
        writeData(0x0);
    }
}

void DMOLED32Display::writeInst(uint8_t data)
{
    writeByte(data, 0);
}

void DMOLED32Display::writeData(uint8_t data)
{
    writeByte(data, 1);
}

void DMOLED32Display::initRegion(int x, int y, int w, int h)
{
    // Physical display region starts at 120.
    x += 120;
    
    writeInst(0x15);
    writeData(x >> 2);
    writeData((x + w - 1) >> 2);

    writeInst(0x75);
    writeData(y);
    writeData(y + h - 1);

    writeInst(0x5c);
}
