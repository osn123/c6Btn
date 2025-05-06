#include <vector>
#include <Btn.h>
std::vector<Button> buttons = {0, 1, 2, 21, 17, 16, 23}; //
#include <Leds.h>
Leds leds;                                               // LEDインスタンス
#include <Display.h>
Display display;

// Button buttons[7] = {0, 1, 2, 21, 17, 16, 23}; // 7ボタン
// --- インスタンス生成 ---


void setup()
{
  display.start();
  leds.start();

  for (auto &btn : buttons)
  {
    btn.start();
  }
}

void loop()
{
  display.update();
  leds.update();

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