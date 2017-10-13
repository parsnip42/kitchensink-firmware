#include "dmoled32display.h"

#ifdef TEENSYDUINO
#include <core_pins.h>
#else
#include <Arduino.h>
#undef min
#undef max
#endif

namespace
{

// TODO: Put all these in the constructor
const int ledPin = 13;
const int db[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
const size_t db_count = sizeof(db)/sizeof(*db);
const int dc = 21;
const int reset = 22;
const int csrw = 23;

inline void writeByte(uint8_t data, int type) __attribute__((always_inline, unused));
inline void writeByte(uint8_t data, int type)
{
#ifdef TEENSYDUINO
    digitalWriteFast(21, type);
    digitalWriteFast(23, 0);

    digitalWriteFast(0, data & 1);
    digitalWriteFast(1, (data >> 1) & 1);
    digitalWriteFast(2, (data >> 2) & 1);
    digitalWriteFast(3, (data >> 3) & 1);
    digitalWriteFast(4, (data >> 4) & 1);
    digitalWriteFast(5, (data >> 5) & 1);
    digitalWriteFast(6, (data >> 6) & 1);
    digitalWriteFast(7, (data >> 7) & 1);
    
    digitalWriteFast(23, 1);
#else
    digitalWrite(21, type);
    digitalWrite(23, 0);

    digitalWrite(0, data & 1);
    digitalWrite(1, (data >> 1) & 1);
    digitalWrite(2, (data >> 2) & 1);
    digitalWrite(3, (data >> 3) & 1);
    digitalWrite(4, (data >> 4) & 1);
    digitalWrite(5, (data >> 5) & 1);
    digitalWrite(6, (data >> 6) & 1);
    digitalWrite(7, (data >> 7) & 1);
    
    digitalWrite(23, 1);
#endif
}

}

DMOLED32Display::DMOLED32Display()
{
    init();
}

void DMOLED32Display::init()
{
    for (size_t i = 0; i < db_count; i++)
    {
        pinMode(db[i], OUTPUT);
    }

    pinMode(dc, OUTPUT);
    pinMode(reset, OUTPUT);
    pinMode(csrw, OUTPUT);

#ifdef TEENSYDUINO
    digitalWriteFast(reset, HIGH);
    delay(200);
    digitalWriteFast(reset, LOW);
    delay(200);
    digitalWriteFast(reset, HIGH);
#else
    digitalWrite(reset, HIGH);
    delay(200);
    digitalWrite(reset, LOW);
    delay(200);
    digitalWrite(reset, HIGH);
#endif
    
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

MutableDataRef DMOLED32Display::rasterLine()
{
    mRasterBuf.fill(0);

    return mRasterBuf;
}

void DMOLED32Display::rasterize(int row)
{
    initRegion(0, row, kWidth, 1);

    for (std::size_t i(0); i < mRasterBuf.size(); i+=2)
    {
        auto a(mRasterBuf[i]);
        auto b(mRasterBuf[i + 1]);
        
        writeData(((a & 0xf) << 4) | (b & 0xf));
    }
}
