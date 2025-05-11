#pragma once
#include <vector>
#include "Btn.h"
#include "IObserver.h" // IObserverインターフェースをインクルード

#include <Adafruit_SSD1306.h> // OLED ディスプレイ用ライブラリ

#define SCREEN_WIDTH 128 // OLED 幅指定
#define SCREEN_HEIGHT 64 // OLED 高さ指定
#define OLED_RESET -1    // リセット端子（未使用 -1）

class Display : public IObserver { // IObserverを継承
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

    Display(); // コンストラクタ
    void start(std::vector<Button>* buttons_ptr_param); // Buttonベクターへのポインタを受け取る
    // void update(std::vector<Button> &btns); // onNotifyとrefreshScreenに分割

    void onNotify(Button* button) override; // Observerの更新メソッド
    void refreshScreen(); // 時間ベースの画面更新処理

private:
    std::vector<Button>* m_buttons_ptr = nullptr; // Buttonベクターへのポインタを保持

    void drawAnimationBarElements(); // アニメーションバーの要素を描画 (lcd.display()なし)
    void drawModeInfo(); // モード情報を描画 (m_buttons_ptrを使用)
    void disp_mode_full_update(); // 現在のモード情報をOLEDに表示 (m_buttons_ptrを使用)
    void rewrite(); // m_buttons_ptrを使用
    void handleAnimationState(); // m_buttons_ptrを使用
};