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
    Button(uint8_t p) : pin(p) {  }

    void start() { pinMode(pin, INPUT_PULLUP); }

    void update()
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
        bool stable = (gauge == gaugeMax);
        if (stable && !lastState)
        {
            state = PRESSED;
            pressTime = millis();
        }
        else if (!stable && lastState)
        {
            if (state == LONG_PRESSED)
                state = RELEASED;
            else
                state = RELEASED;
        }
        else if (stable && lastState && (millis() - pressTime > longPressMs))
        {
            state = LONG_PRESSED;
        }
        lastState = stable;
    }
    bool isPressed() const { return state == PRESSED; }
    bool isLongPressed() const { return state == LONG_PRESSED; }
};
