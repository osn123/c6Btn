#include "Display.h"
// #include <Wire.h> // I2C 通信用ライブラリ

Adafruit_SSD1306 lcd = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void Display::start()
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

void Display::update()
{
    // 状態更新メソッド
    // 必要な処理をここに記述
}