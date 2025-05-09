#include <vector>
#include <Btn.h>
#include <Leds.h>
#include <Display.h>

// std::vector<Button>
// template <class T1>
// using Vec = std::vector<T1>;
// Vec<Button> buttons = {0, 1, 2, 21, 17, 16, 23}; //

using Vec = std::vector<Button>;
Vec buttons = {0, 1, 2, 21, 17, 16, 23}; //

Leds leds;                               // LEDインスタンス
Display display;

void setup()
{
  for (auto &btn : buttons)
  {
    btn.start();
  }
  display.start(buttons);
  leds.start();

}

void loop()
{
  display.update(buttons);
  leds.update(buttons);

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