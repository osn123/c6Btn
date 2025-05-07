#pragma once
#include <Adafruit_NeoPixel.h>
#include <vector> // std::vector を使用するために必要
#include "Btn.h"  // Button 型を使用するために必要

#define NUMPIXELS 10 // 1つ目のNeoPixelのLED数
#define NUMPIXELS2 7 // 2つ目のNeoPixelのLED数
#define PIN 18       // 1つ目のNeoPixelのデータピン
#define PIN2 22      // 2つ目のNeoPixelのデータピン


class Leds
{
public:
    u8_t hue = 55;
    u8_t sat = 100;
    u8_t val = 5;

    typedef enum
    {
        FLAG_A = (1 << 0), // 00000001
        FLAG_B = (1 << 1), // 00000010
        FLAG_C = (1 << 2)  // 00000100
    } FLAG;

    uint8_t status = 0;

    void start();
    void update(const std::vector<Button> &btns);

    void setFlag(u8_t flag);

    void hsv(u8_t h, u8_t s, u8_t v, Adafruit_NeoPixel &pix);
    void clear(Adafruit_NeoPixel &pix);
    void redBtn();
    void clearBtn();
};