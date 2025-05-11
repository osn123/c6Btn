#include "Display.h"

// #include <Wire.h> // I2C 通信用ライブラリ

Adafruit_SSD1306 lcd = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Display::Display() {
    // コンストラクタ (必要なら初期化)
}

void Display::start(std::vector<Button>* buttons_ptr_param)
{
    m_buttons_ptr = buttons_ptr_param; // Buttonベクターへのポインタを保存

    Wire.begin(19, 20); // I2C 通信の初期化（SDA:19, SCL:20）
    if (!lcd.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {                                                     // OLED 初期設定
        Serial.println(F("SSD1306:0 allocation failed")); // エラーメッセージを出力
        while (true)
            ; // 無限ループ
    }
    lcd.setTextColor(SSD1306_WHITE); // 文字色を白に設定
  //  lcd.clearDisplay();              // 画面をクリア
    lcd.display();                   // 画面に反映
}

void Display::onNotify(Button* notifiedButton)
{
    if (!m_buttons_ptr || m_buttons_ptr->empty()) return; // 安全チェック

    // Displayが関心を持つのはbuttons[4] (ピン17) からの通知と仮定
    if (notifiedButton->getPin() == 17) // buttons[4]のピン番号
    {
        // buttons[4]のstatusLとstatusSを参照してDisplayの内部状態を更新
        // ButtonクラスのstatusL/Sはpublicなので直接アクセス可能
        // notifiedButtonはbuttons[4]そのものを指すはず
        state = static_cast<Display::State>(notifiedButton->statusL % 3 + 1);
        state2 = static_cast<Display::State>(notifiedButton->statusS % 3 + 1);
        stateSum = static_cast<Display::State>((notifiedButton->statusL % 3 + 1) * 10 + (notifiedButton->statusS % 3 + 1));
        // 元の if (btns[4].getLongPress() || btns[4].getShortClick()) {} は空だったので、
        // ここで特別な処理がなければ、statusL/Sの参照だけで良い。
    }
}
void Display::refreshScreen() // 時間ベースの画面更新処理
{
    switch (state2)
    {
    case 0:
        break;
    case 1:
        if (millis() - preMillis >= FPS) // 定期的な表示更新（50ms間隔）
        {
            disp_mode_full_update(); // フルアップデート版を呼び出す
            preMillis = millis();        // 時間を更新
        }
        // 状態0の処理
        break;
    case 2:
        // 状態1の処理 (アニメーション)
        handleAnimationState();
        break;
    case STATE_3:
        // 状態2の処理
        rewrite();
        break;
        ;

    default: // デフォルトの処理
        break;
    }
}

void Display::rewrite()
{
    if (!m_buttons_ptr || m_buttons_ptr->empty()) return; // 安全チェック

    if (millis() - preMillis >= FPS) // 定期的な表示更新（50ms間隔）
    {
        lcd.clearDisplay();                    // 表示クリア
        lcd.setTextSize(2);                    // 文字サイズ（2）
        lcd.setCursor(8, 4);                   // 表示開始位置
        lcd.println("Ver" + String(stateSum)); // モード番号を表示

        lcd.setTextSize(1); // 文字サイズを1に変更

        char buffer[8];                           // バッファの宣言
        sprintf(buffer, "%3d", (*m_buttons_ptr)[0].statusS);  // 赤色の値をフォーマット
        lcd.setCursor(62, 0);                     // カーソル位置を設定
        lcd.println("    red " + String(buffer)); // 赤色の値を表示

        sprintf(buffer, "%3d", (*m_buttons_ptr)[0].statusL);  // 緑色の値をフォーマット
        lcd.setCursor(62, 9);                     // カーソル位置を設定
        lcd.println("  green " + String(buffer)); // 緑色の値を表示

        lcd.display();        // 表示実行
        preMillis = millis(); // 時間を更新
    }
}

// モード情報描画のコアロジック (クリアや表示なし)
void Display::drawModeInfo()
{
    if (!m_buttons_ptr || m_buttons_ptr->empty()) return; // 安全チェック
    lcd.setTextSize(2);                    // 文字サイズ（2）
    lcd.setCursor(8, 4);                   // 表示開始位置
    lcd.println("Ver" + String(stateSum)); // モード番号を表示

    lcd.setTextSize(1); // 文字サイズを1に変更

    char buffer[8];                           // バッファの宣言
    sprintf(buffer, "%3d", (*m_buttons_ptr)[0].statusS);  // 赤色の値をフォーマット
    lcd.setCursor(62, 0);                     // カーソル位置を設定
    lcd.println("    red " + String(buffer)); // 赤色の値を表示

    sprintf(buffer, "%3d", (*m_buttons_ptr)[0].statusL);  // 緑色の値をフォーマット
    lcd.setCursor(62, 9);                     // カーソル位置を設定
    lcd.println("  green " + String(buffer)); // 緑色の値を表示

    //   sprintf(buffer, "%3d", pix.blue);  // 青色の値をフォーマット
    lcd.setCursor(62, 18);                    // カーソル位置を設定
    lcd.println("   blue " + String(buffer)); // 青色の値を表示

    //   sprintf(buffer, "%3d", pix.white);  // 白色の値をフォーマット
    lcd.setCursor(62, 27);                    // カーソル位置を設定
    lcd.println("  white " + String(buffer)); // 白色の値を表示

    sprintf(buffer, "%3d", (*m_buttons_ptr)[0].statusL * BRIGHTNESS_MULTIPLIER); // 明るさの値をフォーマット
    lcd.setCursor(62, 45);                        // カーソル位置を設定
    lcd.println("    pow " + String(buffer));     // 明るさの値を表示

    // sprintf(buffer, "%3d", "ee");
    lcd.setCursor(62, 54);                    // カーソル位置を設定
    lcd.println("  speed " + String(buffer)); // 速度情報を表示
}

// 現在のモード情報をOLEDに表示する関数 (クリアと表示込み)
void Display::disp_mode_full_update()
{
    lcd.clearDisplay(); // 表示クリア
    drawModeInfo(); // モード情報を描画
    lcd.display();      // 表示実行
}

void Display::drawAnimationBarElements() // アニメーションバーの要素のみ描画
{
    lcd.fillRect(0, 0, 2, 7 * (animationCounter + 1), SSD1306_WHITE);                               // 左サイドバーを描画
    lcd.fillRect(3, 64 - 7 * (animationCounter + 1), 2, 7 * (animationCounter + 1), SSD1306_WHITE); // 右サイドバーを描画
}

void Display::handleAnimationState()
{
    if (!m_buttons_ptr || m_buttons_ptr->empty()) return; // 安全チェック
    unsigned long currentMillis = millis(); // 現在の時間を取得

    // アニメーションカウンターの更新ロジック (DISPLAY_UPDATE_INTERVAL間隔)
    if (currentMillis - preMillisAnimationCounter >= DISPLAY_UPDATE_INTERVAL)
    {
        if (animationCounter < MAX_ANIMATION_COUNT) // アニメーションカウンタの更新
        {
            animationCounter++;
        }
        else
        {                         // カウンタをリセット
            animationCounter = 0; // カウンタをリセット
        }
        preMillisAnimationCounter = currentMillis; // アニメーションカウンタ用の時間を更新
    }

    // 画面表示の更新ロジック (FPS間隔)
    if (currentMillis - preMillis >= FPS)
    {
        lcd.clearDisplay();         // 最初に画面をクリア
        drawModeInfo();         // モード情報をバッファに描画
        drawAnimationBarElements(); // アニメーションバーをバッファに描画
        lcd.display();              // バッファの内容を一度に表示
        preMillis = currentMillis;  // 画面表示更新用の時間を更新
    }
}