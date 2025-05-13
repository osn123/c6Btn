#include <vector>
#include <Btn.h>
#include <Leds.h>
#include <Display.h>

// #include "Arduino.h"     // Serial通信やdelayのため
// #include "esp_sleep.h"   // esp_sleep_enable_ext0_wakeup, esp_deep_sleep_start のため
// #include "driver/gpio.h"   // GPIO_NUM_x マクロのため
// #include "driver/rtc_io.h" // RTC GPIO関連の関数 (rtc_gpio_pullup_enなど) のため


// #include "IObserver.h" // 間接的にインクルードされる
// #include "ISubject.h"  // 間接的にインクルードされる

// std::vector<Button>
// template <class T1>
// using Vec = std::vector<T1>;
// Vec<Button> buttons = {0, 1, 2, 21, 17, 16, 23}; //

using Vec = std::vector<Button>;
Vec buttons = {0, 1, 2, 21, 17, 16, 23}; //

Leds leds; // LEDインスタンス
Display display;

void setup()
{
  for (auto &btn : buttons)
  {
    btn.start();
  }
  display.start(&buttons); // Displayにbuttonsベクターへのポインタを渡す
  leds.start();

  // ObserverをSubjectに登録
  // Ledsはbuttons[0] (ピン0) と buttons[1] (ピン1) を監視
  buttons[0].attach(&leds);
  buttons[1].attach(&leds);

  // Displayはbuttons[4] (ピン17) を監視
  buttons[4].attach(&display);
  buttons[2].attach(&display);

  // esp_sleep_enable_ext0_wakeup(GPIO_NUM_4, 0);
  // esp_deep_sleep_enable_gpio_wakeup(GPIO_NUM_2, ESP_GPIO_WAKEUP_GPIO_LOW);
  esp_deep_sleep_enable_gpio_wakeup(2, ESP_GPIO_WAKEUP_GPIO_LOW); //TODO:　復帰ピンの設定がうまくいかない

  Serial.begin(115200);
  Serial.println("Hello, world!");
}

void loop()
{
  delay(1); // 時間待ち

  if (Serial.available())
  {
    String cmd = Serial.readStringUntil('\n');
    if (cmd == "rst")
    {
      ESP.restart();
    }
    else if (cmd == "dsp")
    {
      Serial.println("Deep Sleep");
      esp_deep_sleep_start();
    }
  }

  display.refreshScreen(); // Displayの時間ベースの画面更新
  // leds.update(buttons); // LedsはonNotify経由で更新されるため不要

  for (auto &btn : buttons)
  {
    btn.update();
  }

  // for (int i = 0; i < 7; i++)
  // {
  //   buttons[i].update();
  // }

  // ステートマシン例
  // if (buttons[0].isPressed())
  // {
  //   leds.hsv(255, 255, 115, pixels);
  // }
  // else if (buttons[0].isLongPressed())
  // {
  //   leds.clear(pixels);
  // }

  // if (buttons[1].isPressed())
  // {
  //   leds.hsv(leds.hue, leds.sat , leds.val, pixelsBtn);
  // }
  // else if (buttons[1].isLongPressed())
  // {
  //   leds.clear(pixelsBtn);
  // }
  // 他ボタンも同様に
}