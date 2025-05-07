#pragma once

#include <Arduino.h>

class Button
{
    uint8_t pin;
    uint8_t gauge = 5;
    const uint8_t gaugeMax = 10; // ゲージ判定しきい値
    bool lastState = false;
    enum State
    {
        RELEASED,
        PRESSED,
        LONG_PRESSED
    } state = RELEASED;
    unsigned long pressTime = 0;
    const unsigned long longPressMs = 1000;

public:
    Button(uint8_t p);
    void start();
    void update();
    bool isPressed() const;
    bool isLongPressed() const;
};