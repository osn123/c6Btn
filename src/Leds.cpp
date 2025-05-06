#include "Leds.h"

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel pixelsBtn(NUMPIXELS2, PIN2, NEO_GRB + NEO_KHZ800);

void Leds::start()
{
    pixels.begin();
    pixels.show();

    pixelsBtn.begin();
    pixelsBtn.show();
}

void Leds::update(const std::vector<Button> &btns)
{
    if (btns[0].isPressed())
    {
        hsv(hue, sat, val, pixels);
    }
    else if (btns[0].isLongPressed())
    {
        clear(pixels);
    }
    if (btns[1].isPressed())
    {
        hsv(hue * hue, sat * 2, val * 2, pixelsBtn);
    }
    else if (btns[1].isLongPressed())
    {
        clear(pixelsBtn);
    }
}
void Leds::setFlag(u8_t flag)
{
    status |= flag; // フラグをON
}


void Leds::hsv(u8_t h, u8_t s, u8_t v, Adafruit_NeoPixel &pix)
{
    for (uint16_t i = 0; i < pix.numPixels(); i++)
    {
        pix.setPixelColor(i, pix.ColorHSV(h * h, s, v));
    }
    pix.show();
}

void Leds::clear(Adafruit_NeoPixel &pix)
{
    for (uint16_t i = 0; i < pix.numPixels(); i++)
    {
        pix.setPixelColor(i, pix.Color(0, 0, 0));
    }
    pix.show();
}

void Leds::redBtn()
{
    for (uint16_t i = 0; i < pixelsBtn.numPixels(); i++)
    {
        pixelsBtn.setPixelColor(i, pixelsBtn.Color(150, 0, 0));
    }
    pixelsBtn.show();
}

void Leds::clearBtn()
{
    for (uint16_t i = 0; i < pixelsBtn.numPixels(); i++)
    {
        pixelsBtn.setPixelColor(i, pixelsBtn.Color(0, 0, 0));
    }
    pixelsBtn.show();
}