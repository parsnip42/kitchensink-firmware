#ifndef INCLUDED_AFILI9431DISPLAY_H
#define INCLUDED_AFILI9431DISPLAY_H

#include "hardware/display.h"

#include "Adafruit_ILI9341.h"

class AFILI9431Display : public Display
{
private:
    // Rotated by default - not a typo!
    static constexpr int kWidth  = ILI9341_TFTHEIGHT;
    static constexpr int kHeight = ILI9341_TFTWIDTH;

public:
    AFILI9431Display();

public:
    virtual int width() const override;
    virtual int height() const override;
    virtual MutableDataRef rasterLine() override;
    virtual void rasterize(int row) override;
    virtual void clear() override;

private:
    Adafruit_ILI9341            mDisplay;
    std::array<uint8_t, kWidth> mRasterBuf;
};


inline
int AFILI9431Display::width() const
{
    return kWidth;
}

inline
int AFILI9431Display::height() const
{
    return kHeight;
}

#endif
