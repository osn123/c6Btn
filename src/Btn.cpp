#include "Btn.h"

Button::Button(uint8_t p) : pin(p), state(RELEASED), lastState(false), pressTime(0), m_shortClickEvent(false), m_longPressEvent(false)
{
}

void Button::start()
{
    pinMode(pin, INPUT_PULLUP);
    lastState = !digitalRead(pin); // 現在の物理的な状態に基づいて lastState を初期化
}

void Button::update()
{
    bool reading = !digitalRead(pin); // プルアップなので反転
    if (reading)
    {
        if (gauge < gaugeMax)
            gauge++;
    }
    else
    {
        if (gauge > 0)
            gauge--;
    }

    // 前回のサイクルのワンショットイベントをクリア
    m_shortClickEvent = false;
    m_longPressEvent = false;

    bool stable = (gauge == gaugeMax);

    if (stable && !lastState)
    {
        // ボタンが押されたばかり
        state = PRESSED;
        pressTime = millis();
    }
    else if (!stable && lastState)
    {
        // ボタンが離されたばかり
        if (state == PRESSED) // まだ LONG_PRESSED 状態でない場合
        {
            m_shortClickEvent = true; // ショートクリックイベントを設定
        }
        // 前の状態が PRESSED または LONG_PRESSED に関係なく、現在は RELEASED
        state = RELEASED;
    }
    else if (stable && lastState && state == PRESSED) // ボタンが押され続けていて、PRESSED 状態だった場合
    {
        if (millis() - pressTime > longPressMs)
        {
            state = LONG_PRESSED;
            m_longPressEvent = true; // ロングプレスイベントを設定
        }
    }
    lastState = stable;
}

bool Button::getShortClick()
{
    if (m_shortClickEvent)
    {
        m_shortClickEvent = false; // イベントを消費
        statusS++;
        return true;
    }
    return false;
}

bool Button::getLongPress()
{
    if (m_longPressEvent)
    {
        statusL++;
        m_longPressEvent = false; // イベントを消費
        return true;
    }
    return false;
}

bool Button::isCurrentlyPressed() const
{
    // ボタンが物理的に押されているかどうかを確認するために使用できます。
    // ショート/ロングプレスイベントに関係なく状態を確認します。
    return (state == PRESSED || state == LONG_PRESSED);
}