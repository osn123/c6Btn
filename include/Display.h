#pragma once
#include <vector>
#include "Btn.h"

#include <Adafruit_SSD1306.h> // OLED ディスプレイ用ライブラリ

#define SCREEN_WIDTH 128 // OLED 幅指定
#define SCREEN_HEIGHT 64 // OLED 高さ指定
#define OLED_RESET -1    // リセット端子（未使用 -1）

class Display{
public:
    unsigned long preMillis = 0; // 前回の更新時間
    const long interval = 500;        // 更新間隔（500ms）
    const long FPS = 1000/30;        // 更新間隔（30fps）
    uint8_t animationCounter = 0; // アニメーションカウンタ

    const int DISPLAY_UPDATE_INTERVAL = 500;  // ディスプレイ更新間隔（ミリ秒）
    unsigned long preMillisAnimationCounter = 0; // アニメーションカウンタ更新用の前回時間
    const uint8_t MAX_ANIMATION_COUNT = 8;        // アニメーションの最大カウント
    const uint8_t BRIGHTNESS_MULTIPLIER = 10;     // 明るさの乗数
    
    enum State
    {
        STATE_0=0,
        STATE_1,
        STATE_2,
        STATE_3,
        STATE_4,
        STATE_5,
        STATE_6,
        STATE_7
    } state = STATE_1, state2 = STATE_1, stateSum = STATE_0; // 現在の状態を保持する変数

    void start(std::vector<Button> &btns);
    void update(std::vector<Button> &btns);

    void rewrite(std::vector<Button> &btns);

    void handleAnimationState(std::vector<Button> &btns);

private:
    void drawAnimationBarElements(); // アニメーションバーの要素を描画 (lcd.display()なし)
    void drawModeInfo(std::vector<Button> &btns); // モード情報を描画 (lcd.clearDisplay() と lcd.display()なし)
    void disp_mode_full_update(std::vector<Button> &btns) ;// 現在のモード情報をOLEDに表示する関数 (クリアと表示込み)
   
};