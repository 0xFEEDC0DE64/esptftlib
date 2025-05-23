#pragma once

// system includes
#include <cstdint>

// local includes
#include "icon.h"

namespace espgui {
class TftInterface
{
public:
    explicit TftInterface() = default;
    virtual ~TftInterface() = default;

    virtual void     begin_tft_write() = 0;
    virtual void     end_tft_write() = 0;

    virtual void     setWindow(int32_t xs, int32_t ys, int32_t xe, int32_t ye) = 0;

    virtual void     Write_16(uint16_t v) = 0;

    virtual void     pushBlock(uint16_t color, uint32_t len) = 0;

    virtual void     drawPixel(int32_t x, int32_t y, uint16_t color) = 0;
    virtual void     drawArc(int32_t x, int32_t y, int32_t r, int32_t ir, uint32_t startAngle, uint32_t endAngle, uint32_t fg_color, uint32_t bg_color, bool smoothArc = true) = 0;
    virtual void     drawLine(int32_t xs, int32_t ys, int32_t xe, int32_t ye, uint16_t color) = 0;
    virtual void     drawFastVLine(int32_t x, int32_t y, int32_t h, uint16_t color) = 0;
    virtual void     drawFastHLine(int32_t x, int32_t y, int32_t w, uint16_t color) = 0;
    virtual void     fillRect(int32_t x, int32_t y, int32_t w, int32_t h, uint16_t color) = 0;

    virtual int16_t  height(void) const = 0;
    virtual int16_t  width(void) const = 0;

    virtual void     setRotation(uint8_t r) = 0; // Set the display image orientation to 0, 1, 2 or 3
    virtual uint8_t  getRotation(void) const = 0;      // Read the current rotation

    // Graphics drawing
    virtual void     fillScreen(uint32_t color) = 0;
    virtual void     drawRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color) = 0;
    virtual void     drawRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t radius, uint32_t color) = 0;
    virtual void     fillRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t radius, uint32_t color) = 0;

    virtual void     fillRectVGradient(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color1, uint32_t color2) = 0;
    virtual void     fillRectHGradient(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color1, uint32_t color2) = 0;

    // Draw a small anti-aliased filled circle at ax,ay with radius r (uses drawWideLine)
    // If bg_color is not included the background pixel colour will be read from TFT or sprite
    virtual void     drawSpot(float ax, float ay, float r, uint32_t fg_color, uint32_t bg_color = 0x00FFFFFF) = 0;

    // Draw an anti-aliased filled circle at x, y with radius r
    // If bg_color is not included the background pixel colour will be read from TFT or sprite
    virtual void     fillSmoothCircle(int32_t x, int32_t y, int32_t r, uint32_t color, uint32_t bg_color = 0x00FFFFFF) = 0;

    virtual void     fillSmoothRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t radius, uint32_t color, uint32_t bg_color = 0x00FFFFFF) = 0;

    // Draw an anti-aliased wide line from ax,ay to bx,by width wd with radiused ends (radius is wd/2)
    // If bg_color is not included the background pixel colour will be read from TFT or sprite
    virtual void     drawWideLine(float ax, float ay, float bx, float by, float wd, uint32_t fg_color, uint32_t bg_color = 0x00FFFFFF) = 0;

    // Draw an anti-aliased wide line from ax,ay to bx,by with different width at each end aw, bw and with radiused ends
    // If bg_color is not included the background pixel colour will be read from TFT or sprite
    virtual void     drawWedgeLine(float ax, float ay, float bx, float by, float aw, float bw, uint32_t fg_color, uint32_t bg_color = 0x00FFFFFF) = 0;

    virtual void     drawSunkenRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color0, uint32_t color1, uint32_t color2) = 0;

    virtual void     drawCircle(int32_t x, int32_t y, int32_t r, uint32_t color) = 0;
    virtual void     drawCircleHelper(int32_t x, int32_t y, int32_t r, uint8_t cornername, uint32_t color) = 0;
    virtual void     fillCircle(int32_t x, int32_t y, int32_t r, uint32_t color) = 0;
    virtual void     fillCircleHelper(int32_t x, int32_t y, int32_t r, uint8_t cornername, int32_t delta, uint32_t color) = 0;

    virtual void     drawEllipse(int16_t x, int16_t y, int32_t rx, int32_t ry, uint16_t color) = 0;
    virtual void     fillEllipse(int16_t x, int16_t y, int32_t rx, int32_t ry, uint16_t color) = 0;

    //                                   Corner 1               Corner 2               Corner 3
    virtual void     drawTriangle(int32_t x1,int32_t y1, int32_t x2,int32_t y2, int32_t x3,int32_t y3, uint32_t color) = 0;
    virtual void     fillTriangle(int32_t x1,int32_t y1, int32_t x2,int32_t y2, int32_t x3,int32_t y3, uint32_t color) = 0;

    // These are used to render images or sprites stored in RAM arrays (used by Sprite class for 16bpp Sprites)
    template<uint16_t width, uint16_t height>
    void pushImage(int32_t x, int32_t y, const Icon<width, height> &icon)
    {
        pushImage(x, y, width, height, icon.buffer);
    }
    template<uint16_t width, uint16_t height>
    void pushImage(int32_t x, int32_t y, const Icon<width, height> &icon, uint16_t transparent)
    {
        pushImage(x, y, width, height, icon.buffer, transparent);
    }
    virtual void     pushImage(int32_t x, int32_t y, int32_t w, int32_t h, const uint16_t *data) = 0;
    virtual void     pushImage(int32_t x, int32_t y, int32_t w, int32_t h, const uint16_t *data, uint16_t transparent) = 0;

    // Bare metal functions
    virtual void     startWrite(void) = 0;
    virtual void     writeColor(uint16_t color, uint32_t len) = 0;
    virtual void     endWrite(void) = 0;

    // Push (aka write pixel) colours to the set window
    virtual void     pushColor(uint16_t color, uint32_t len) = 0;

    // The TFT_eSprite class inherits the following functions (not all are useful to Sprite class
    virtual void     setAddrWindow(int32_t xs, int32_t ys, int32_t w, int32_t h) = 0;
};

inline bool isLandscape(const TftInterface &tft)
{
    return (tft.getRotation() == 1 || tft.getRotation() == 3);
}
} // namespace espgui
