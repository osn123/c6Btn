#pragma once
#include <Adafruit_NeoPixel.h>

#define NUMPIXELS 10 // 1つ目のNeoPixelのLED数
#define NUMPIXELS2 7 // 2つ目のNeoPixelのLED数
#define PIN 18       // 1つ目のNeoPixelのデータピン
#define PIN2 22      // 2つ目のNeoPixelのデータピン

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);     //
Adafruit_NeoPixel pixelsBtn(NUMPIXELS2, PIN2, NEO_GRB + NEO_KHZ800); //

class Leds
{
public:
    u8_t hue = 55;
    u8_t sat = 100;
    u8_t val = 5;

    void start()
    {
        pixels.begin();
        pixels.show();

        pixelsBtn.begin();
        pixelsBtn.show();
    }
    void update()
    {
        if (buttons[0].isPressed())
        {
            hsv(hue, sat, val, pixels );
        }
        else if (buttons[0].isLongPressed())
        {
            clear(pixels);
        }
        if (buttons[1].isPressed())
        {
            hsv(hue*hue, sat*2, val*2, pixelsBtn);
        }
        else if (buttons[1].isLongPressed())
        {
            clear(pixelsBtn);
        }
    }

    void hsv(u8_t h, u8_t s, u8_t v, Adafruit_NeoPixel &pix)
    {
        for (uint16_t i = 0; i < pix.numPixels(); i++)
        {
            // pix.setPixelColor(i, pix.Color(0, 0, 150));
            pix.setPixelColor(i, pix.ColorHSV(h * h, s, v));
        }
        pix.show();
    }

    void clear(Adafruit_NeoPixel &pix)
    {
        for (uint16_t i = 0; i < pix.numPixels(); i++)
        {
            pix.setPixelColor(i, pix.Color(0, 0, 0));
        }
        pix.show();
    }

    void redBtn()
    {
        for (uint16_t i = 0; i < pixelsBtn.numPixels(); i++)
        {
            pixelsBtn.setPixelColor(i, pixelsBtn.Color(150, 0, 0));
        }
        pixelsBtn.show();
    }

    void clearBtn()
    {
        for (uint16_t i = 0; i < pixelsBtn.numPixels(); i++)
        {
            pixelsBtn.setPixelColor(i, pixelsBtn.Color(0, 0, 0));
        }
        pixelsBtn.show();
    }
};
