#ifndef INCLUDED_DMOLED32DISPLAY_H
#define INCLUDED_DMOLED32DISPLAY_H

#include "hardware/display.h"

class DMOLED32Display : public Display
{
private:
    static constexpr int kWidth  = 240;
    static constexpr int kHeight = 64;
    
public:
    DMOLED32Display();

public:
    virtual int width() const override;
    virtual int height() const override;
    virtual MutableDataRef rasterLine() override;
    virtual void rasterize(int row) override;
    virtual void clear() override;
    
private:
    void init();
    void initRegion(int x, int y, int w, int h);
    void writeInst(uint8_t data);
    void writeData(uint8_t data);

private:
    std::array<uint8_t, kWidth> mRasterBuf;
    
private:
    DMOLED32Display(const DMOLED32Display&) = delete;
    DMOLED32Display& operator=(const DMOLED32Display&) = delete;
};


inline
int DMOLED32Display::width() const
{
    return kWidth;
}

inline
int DMOLED32Display::height() const
{
    return kHeight;
}

#endif
