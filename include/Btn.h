#pragma once
#include <Arduino.h>

class Button
{
    uint8_t pin;
    uint8_t gauge = 0;
    const uint8_t gaugeMax = 5; // ゲージ判定しきい値
    bool lastState = false;
    enum State
    {
        RELEASED,
        PRESSED,
        LONG_PRESSED
    } state = RELEASED;
    unsigned long pressTime = 0;
    const unsigned long longPressMs = 1000;
    
    // Event flags
    bool m_shortClickEvent;
    bool m_longPressEvent;

public:

     u8_t  statusS= 0; // ボタンの状態を保持する変数
     u8_t statusL = 0; // ボタンの状態を保持する変数

    Button(uint8_t p);
    void start();
    void update();
    bool getShortClick(); // True if a short click just occurred (consumes event)
    bool getLongPress();  // True if a long press just started (consumes event)
    bool isCurrentlyPressed() const; // Optional: To check if button is physically down

    
};