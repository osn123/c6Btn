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
    lcd.clearDisplay();              // 画面をクリア
    lcd.display();                   // 画面に反映
}

void Display::update(std::vector<Button> &btns)
{
    state = static_cast<Display::State>(btns[4].statusL % 3); // ボタンの状態を取得
    state2 = static_cast<Display::State>(btns[4].statusS % 3); // ボタンの状態を取得
    stateSum = static_cast<Display::State>((btns[4].statusL% 3)*10 + btns[4].statusS% 3); // ボタンの状態を取得

    if (btns[4].getLongPress()||btns[4].getShortClick())
    { 
    }

    switch (state2)
    {
    case 0:
        if (millis() - preMillis >= FPS) // 定期的な表示更新（50ms間隔）
        {
            disp_mode_full_update(btns); // フルアップデート版を呼び出す
            preMillis = millis(); // 時間を更新
        }
        // 状態0の処理
        break;
    case 1:
        // 状態1の処理 (アニメーション)
        handleAnimationState(btns);
        break;
    case STATE_2:
        // 状態2の処理
        rewrite(btns);
        break;
        ;

    default: // デフォルトの処理
        break;
    }
}

void Display::rewrite(std::vector<Button> &btns)
{

    if (millis() - preMillis >= FPS) // 定期的な表示更新（50ms間隔）
    {
        lcd.clearDisplay();                 // 表示クリア
        lcd.setTextSize(2);                 // 文字サイズ（2）
        lcd.setCursor(8, 4);                // 表示開始位置
        lcd.println("Ver" + String(stateSum)); // モード番号を表示

        lcd.setTextSize(1); // 文字サイズを1に変更

        char buffer[8];                           // バッファの宣言
        sprintf(buffer, "%3d", btns[0].statusS);  // 赤色の値をフォーマット
        lcd.setCursor(62, 0);                     // カーソル位置を設定
        lcd.println("    red " + String(buffer)); // 赤色の値を表示

        sprintf(buffer, "%3d", btns[0].statusL);  // 緑色の値をフォーマット
        lcd.setCursor(62, 9);                     // カーソル位置を設定
        lcd.println("  green " + String(buffer)); // 緑色の値を表示

        lcd.display();        // 表示実行
        preMillis = millis(); // 時間を更新
    }
}

// モード情報描画のコアロジック (クリアや表示なし)
void Display::drawModeInfo(std::vector<Button> &btns)
{
    lcd.setTextSize(2);                 // 文字サイズ（2）
    lcd.setCursor(8, 4);                // 表示開始位置
    lcd.println("Ver" + String(stateSum)); // モード番号を表示

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

}

// 現在のモード情報をOLEDに表示する関数 (クリアと表示込み)
void Display::disp_mode_full_update(std::vector<Button> &btns)
{
    lcd.clearDisplay(); // 表示クリア
    drawModeInfo(btns); // モード情報を描画
    lcd.display(); // 表示実行
}

void Display::drawAnimationBarElements() // アニメーションバーの要素のみ描画
{
    lcd.fillRect(0, 0, 2, 7 * (animationCounter + 1), SSD1306_WHITE);                               // 左サイドバーを描画
    lcd.fillRect(3, 64 - 7 * (animationCounter + 1), 2, 7 * (animationCounter + 1), SSD1306_WHITE); // 右サイドバーを描画
}

void Display::handleAnimationState(std::vector<Button> &btns)
{
    unsigned long currentMillis = millis(); // 現在の時間を取得

    // アニメーションカウンターの更新ロジック (DISPLAY_UPDATE_INTERVAL間隔)
    if (currentMillis - preMillisAnimationCounter >= DISPLAY_UPDATE_INTERVAL)
    {
        if (animationCounter < MAX_ANIMATION_COUNT) // アニメーションカウンタの更新
        {
            animationCounter++;
        }
        else
        { // カウンタをリセット
            animationCounter = 0; // カウンタをリセット
        }
        preMillisAnimationCounter = currentMillis; // アニメーションカウンタ用の時間を更新
    }

    // 画面表示の更新ロジック (FPS間隔)
    if (currentMillis - preMillis >= FPS)
    {
        lcd.clearDisplay(); // 最初に画面をクリア
        drawModeInfo(btns); // モード情報をバッファに描画
        drawAnimationBarElements(); // アニメーションバーをバッファに描画
        lcd.display(); // バッファの内容を一度に表示
        preMillis = currentMillis; // 画面表示更新用の時間を更新
    }
}