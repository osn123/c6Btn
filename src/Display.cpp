#include "Display.h"

// #include <Wire.h> // I2C 通信用ライブラリ

Adafruit_SSD1306 lcd = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void Display::start(std::vector<Button> &btns)
{
    Wire.begin(19, 20); // I2C 通信の初期化（SDA:19, SCL:20）
    if (!lcd.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {                                                     // OLED 初期設定
        Serial.println(F("SSD1306:0 allocation failed")); // エラーメッセージを出力
        while (true)
            ; // 無限ループ
    }
    lcd.setTextColor(SSD1306_WHITE); // 文字色を白に設定
    lcd.display();                   // 画面に反映
}

void Display::update(std::vector<Button> &btns)
{
    if (btns[4].getLongPress())
    {
    }
    switch (btns[4].statusL % 3)
    {
    case 0:
        if (millis() - preMillis >= FPS) // 定期的な表示更新（50ms間隔）
        {

            disp_mode(btns);
            preMillis = millis(); // 時間を更新
        }
        // 状態0の処理
        break;
    case 1:
        // 状態1の処理
        handleAnimation(btns);
        break;
    case STATE_2:
        // 状態2の処理
        rewrite(btns);
        break;
        ;

    default:

        // デフォルトの処理
        break;
    }

    // 状態更新メソッド
    // 必要な処理をここに記述;
    // handleAnimation(btns);
}

void Display::rewrite(std::vector<Button> &btns)
{

    if (millis() - preMillis >= FPS) // 定期的な表示更新（50ms間隔）
    {
        lcd.clearDisplay();                           // 表示クリア
        lcd.setTextSize(2);                           // 文字サイズ（2）
        lcd.setCursor(8, 4);                          // 表示開始位置
        lcd.println("Ver" + String(btns[4].statusL)); // モード番号を表示

        lcd.display();        // 表示実行
        preMillis = millis(); // 時間を更新
    }
}

void Display::drawAnimationBars()
{
    lcd.fillRect(0, 0, 2, 7 * (animationCounter + 1), SSD1306_WHITE);                               // 左サイドバーを描画
    lcd.fillRect(3, 64 - 7 * (animationCounter + 1), 2, 7 * (animationCounter + 1), SSD1306_WHITE); // 右サイドバーを描画
}

// 現在のモード情報をOLEDに表示する関数
void Display::disp_mode(std::vector<Button> &btns) // 現在のモード情報をOLEDに表示する関数
{
    lcd.clearDisplay();                           // 表示クリア
    lcd.setTextSize(2);                           // 文字サイズ（2）
    lcd.setCursor(8, 4);                          // 表示開始位置
    lcd.println("Ver" + String(btns[4].statusL)); // モード番号を表示

    lcd.setTextSize(1); // 文字サイズを1に変更

    char buffer[8];                           // バッファの宣言
    sprintf(buffer, "%3d", btns[0].statusS);  // 赤色の値をフォーマット
    lcd.setCursor(62, 0);                     // カーソル位置を設定
    lcd.println("    red " + String(buffer)); // 赤色の値を表示

    sprintf(buffer, "%3d", btns[0].statusL);  // 緑色の値をフォーマット
    lcd.setCursor(62, 9);                     // カーソル位置を設定
    lcd.println("  green " + String(buffer)); // 緑色の値を表示

    //   sprintf(buffer, "%3d", pix.blue);  // 青色の値をフォーマット
    lcd.setCursor(62, 18);                    // カーソル位置を設定
    lcd.println("   blue " + String(buffer)); // 青色の値を表示

    //   sprintf(buffer, "%3d", pix.white);  // 白色の値をフォーマット
    lcd.setCursor(62, 27);                    // カーソル位置を設定
    lcd.println("  white " + String(buffer)); // 白色の値を表示

    sprintf(buffer, "%3d", btns[0].statusL * 10); // 明るさの値をフォーマット
    lcd.setCursor(62, 45);                        // カーソル位置を設定
    lcd.println("    pow " + String(buffer));     // 明るさの値を表示

    // sprintf(buffer, "%3d", "ee");
    lcd.setCursor(62, 54);                    // カーソル位置を設定
    lcd.println("  speed " + String(buffer)); // 速度情報を表示

    lcd.display(); // 表示実行
}

void Display::handleAnimation(std::vector<Button> &btns)
{
    unsigned long currentMillis = millis();                   // 現在の時間を取得
    if (currentMillis - preMillis >= DISPLAY_UPDATE_INTERVAL) // 定期的な表示更新（500ms間隔）
    {
        drawAnimationBars();
        lcd.display();             // 表示実行
        preMillis = currentMillis; // 時間を更新

        if (animationCounter < MAX_ANIMATION_COUNT) // アニメーションカウンタの更新
        {
            animationCounter++;
        }
        else
        {
            animationCounter = 0; // カウンタをリセット
            disp_mode(btns);      // モード情報を表示
        }
    }
}