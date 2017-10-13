#include "afili9431display.h"

AFILI9431Display::AFILI9431Display()
    : mDisplay(9, 10)
{
    mDisplay.begin();
    mDisplay.setRotation(1);
    mDisplay.fillScreen(ILI9341_RED);
    clear();
}

MutableDataRef AFILI9431Display::rasterLine()
{
    mRasterBuf.fill(0);

    return mRasterBuf;
}

void AFILI9431Display::rasterize(int row)
{
    mDisplay.startWrite();
    mDisplay.setAddrWindow(0, row, kWidth, 1);

    for (auto pixel : mRasterBuf)
    {
        mDisplay.writePixel(pixel ? ILI9341_WHITE : ILI9341_BLACK);
    }

    mDisplay.endWrite();
}

void AFILI9431Display::clear()
{
    mDisplay.fillScreen(ILI9341_BLACK);
}


