#pragma once
#include <Adafruit_NeoPixel.h>
#include <vector> // std::vector を使用するために必要
#include "Btn.h"  // Button 型を使用するために必要
#include "IObserver.h" // IObserverインターフェースをインクルード

#define NUMPIXELS 10 // 1つ目のNeoPixelのLED数
#define NUMPIXELS2 7 // 2つ目のNeoPixelのLED数
#define PIN 18       // 1つ目のNeoPixelのデータピン
#define PIN2 22      // 2つ目のNeoPixelのデータピン


class Leds : public IObserver // IObserverを継承
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

    u8_t status = 0;

    void start();
    // void update(std::vector<Button> &btns); // onNotifyに置き換えられる
    void onNotify(Button* button) override; // Observerの更新メソッド

    void setFlag(u8_t flag);

    void hsv(u8_t h, u8_t s, u8_t v, Adafruit_NeoPixel &pix);
    void clear(Adafruit_NeoPixel &pix);
    void redBtn();
    void clearBtn();
    
};