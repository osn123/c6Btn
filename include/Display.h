#pragma once

#include <Adafruit_SSD1306.h> // OLED ディスプレイ用ライブラリ

#define SCREEN_WIDTH 128                                              // OLED 幅指定
#define SCREEN_HEIGHT 64                                              // OLED 高さ指定
#define OLED_RESET -1                                                 // リセット端子（未使用 -1）
Adafruit_SSD1306 lcd(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // OLED ディスプレイの設定

class Display
{
public:
    void start()
    {
        Wire.begin(19, 20); // I2C 通信の初期化（SDA:19, SCL:20）
        if (!lcd.begin(SSD1306_SWITCHCAPVCC, 0x3C))
        {                                                     // OLED 初期設定
            Serial.println(F("SSD1306:0 allocation failed")); // エラーメッセージを出力
            while (true)
                ; // 無限ループ
        }
        lcd.display(); // 画面に反映

        // lcd.setTextColor(SSD1306_WHITE); // 文字色を白に設定
        // lcd.clearDisplay(); // 画面をクリア
        // lcd.setCursor(0, 0); // カーソルを設定
        // lcd.print("Hello, World!"); // テキストを表示
    }

    void update()
    { // 状態更新メソッド
      // 必要な処理をここに記述
    }

private:
    // プライベートメンバはなし
};