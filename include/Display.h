#pragma once
#include <vector>
#include "Btn.h"


#include <Adafruit_SSD1306.h> // OLED ディスプレイ用ライブラリ


#define SCREEN_WIDTH 128 // OLED 幅指定
#define SCREEN_HEIGHT 64 // OLED 高さ指定
#define OLED_RESET -1    // リセット端子（未使用 -1）

class Display
{
public:
    unsigned long preMillis = 0; // 前回の更新時間
    const long interval = 500;        // 更新間隔（500ms）
    const long FPS = 1000/30;        // 更新間隔（30fps）
    uint8_t animationCounter = 0; // アニメーションカウンタ

    const int DISPLAY_UPDATE_INTERVAL = 500;  // ディスプレイ更新間隔（ミリ秒）
    const uint8_t MAX_ANIMATION_COUNT = 8;        // アニメーションの最大カウント
    const uint8_t BRIGHTNESS_MULTIPLIER = 10;     // 明るさの乗数

    void start(std::vector<Button> &btns);
    void update(std::vector<Button> &btns);

    void handleAnimation(std::vector<Button> &btns);

    void drawAnimationBars();
    void disp_mode(std::vector<Button> &btns) ;// 現在のモード情報をOLEDに表示する関数

    
};