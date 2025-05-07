#pragma once

#include <Adafruit_SSD1306.h> // OLED ディスプレイ用ライブラリ

#define SCREEN_WIDTH 128                                              // OLED 幅指定
#define SCREEN_HEIGHT 64                                              // OLED 高さ指定
#define OLED_RESET -1                                                 // リセット端子（未使用 -1）

class Display
{
public:
    void start();
    void update();
};