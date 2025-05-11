#include "Btn.h"

Button::Button(uint8_t p)
    : pin(p), state(RELEASED), lastState(false), pressTime(0), m_shortClickEvent(false), m_longPressEvent(false)
{
}

void Button::start()
{
    pinMode(pin, INPUT_PULLUP);    // ピンをプルアップ入力に設定
    lastState = !digitalRead(pin); // 現在の物理状態でlastStateを初期化
}

void Button::update()
{
    bool reading = !digitalRead(pin); // プルアップなので論理を反転
    if (reading)
    {
        if (gauge < gaugeMax)
            gauge++; // 押されていればゲージを増加
    }
    else
    {
        if (gauge > 0)
            gauge--; // 離されていればゲージを減少
    }

    m_shortClickEvent = false; // 前回のショートクリックイベントをクリア
    m_longPressEvent = false;  // 前回のロングプレスイベントをクリア

    bool stable = (gauge == gaugeMax); // ゲージが最大なら安定とみなす

    if (stable && !lastState)
    {
        state = PRESSED;      // ボタンが押されたばかり
        pressTime = millis(); // 押された時刻を記録
    }
    else if (!stable && lastState)
    {
        if (state == PRESSED)
        {
            m_shortClickEvent = true; // ショートクリックイベントをセット
            statusS++;                // ショートクリック回数をここでカウント
            notify(this);             // Observerに通知
        }
        state = RELEASED; // 状態をリリースに戻す
    }
    else if (stable && lastState && state == PRESSED)
    {
        // stateがPRESSEDからLONG_PRESSEDに遷移する場合
        if (millis() - pressTime > longPressMs)
        {
            state = LONG_PRESSED;    // ロングプレス状態へ移行
            m_longPressEvent = true; // ロングプレスイベントをセット
            statusL++;               // ロングプレス回数をここでカウント
            notify(this);            // Observerに通知
        }
    }
    lastState = stable; // lastStateを更新
}

bool Button::getShortClick()
{
    if (m_shortClickEvent)
    {
        m_shortClickEvent = false; // イベントを消費
        // statusS++; // ショートクリック回数をカウント
        return true;
    }
    return false;
}

bool Button::getLongPress()
{
    if (m_longPressEvent)
    {
        m_longPressEvent = false; // イベントを消費
        // statusL++; // ロングプレス回数をカウント
        return true;
    }
    return false;
}

bool Button::isCurrentlyPressed() const
{
    return (state == PRESSED || state == LONG_PRESSED); // 現在押されているか判定
}
