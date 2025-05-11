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

void Leds::onNotify(Button *button)
{
    uint8_t notifiedPin = button->getPin();

    // buttons[0] (ピン0) と buttons[1] (ピン1) に対応する処理
    // main.cppでの初期化ピン番号を想定
    if (notifiedPin == 0) // 元のbtns[0]に対応
    {
        if (button->getLongPress()) // まずロングプレスイベントをチェック
        {
            clear(pixels); // ロングプレス時のアクション
        }
        else if (button->getShortClick()) // ロングプレスでなければショートクリックをチェック
        {
            hsv(hue, sat, val, pixels,button); // ショートクリック時のアクション
        }
    }
    else if (notifiedPin == 1) // 元のbtns[1]に対応
    {
        if (button->getLongPress())
        {
            clear(pixelsBtn);
        }
        else if (button->getShortClick())
        {
            hsv(hue, sat, val, pixelsBtn,button);
        }
    }
}
void Leds::setFlag(u8_t flag)
{
    status |= flag; // フラグをON
}

void Leds::hsv(u8_t h, u8_t s, u8_t v, Adafruit_NeoPixel &pix, Button *button)
{
    // for (uint16_t i = 0; i < pix.numPixels(); i++)
    // {
    //     pix.setPixelColor(i, pix.ColorHSV((i * 65536L) / pix.numPixels(), s, v));
    // }

    pix.setPixelColor(button->statusS % pix.numPixels(), pix.ColorHSV((button->statusS % pix.numPixels() * 65536L) / pix.numPixels(), s, v));

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