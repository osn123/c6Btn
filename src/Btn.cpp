#include "Btn.h"

Button::Button(uint8_t p) : pin(p) {}

void Button::start()
{
    pinMode(pin, INPUT_PULLUP);
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

bool Button::isPressed() const
{
    return state == PRESSED && state != LONG_PRESSED; // LONG_PRESSED のときは false を返す
}

bool Button::isLongPressed() const
{
    return state == LONG_PRESSED;
}