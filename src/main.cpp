#include <vector>
#include <Btn.h>
#include <Leds.h>
#include <Display.h>
#include "secret.h"
#include <WiFi.h>
#include <WebServer.h>

// --- グローバル変数・インスタンス定義 ---
WebServer server(80); // Webサーバー(ポート80)
using Vec = std::vector<Button>;
Vec buttons = {0, 1, 2, 21, 17, 16, 23}; // ボタン配列

Leds leds;      // LED制御インスタンス
Display display; // OLED表示インスタンス

// --- Webサーバーハンドラ ---
void handleRoot() {
  server.send(200, "text/plain", "Hello from XIAO ESP32C6!");
}

// --- セットアップ ---
void setup()
{
  // ボタン初期化
  for (auto &btn : buttons) btn.start();

  // ディスプレイ・LED初期化
  display.start(&buttons);
  leds.start();

  // オブザーバ登録
  buttons[0].attach(&leds); // LED制御用
  buttons[1].attach(&leds);
  buttons[4].attach(&display); // Display制御用
  buttons[2].attach(&display);

  // スリープ復帰ピン設定
  esp_deep_sleep_enable_gpio_wakeup(2, ESP_GPIO_WAKEUP_GPIO_LOW);
  gpio_wakeup_enable(GPIO_NUM_2, GPIO_INTR_LOW_LEVEL);
  esp_sleep_enable_gpio_wakeup();

  // シリアル通信
  Serial.begin(115200);
  Serial.println("Hello, world!");

  // WiFi接続
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.println(WiFi.localIP());

  // Webサーバー開始
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}

// --- メインループ ---
void loop()
{
  delay(1); // 負荷軽減用

  server.handleClient(); // Webサーバー応答

  // シリアルコマンド受付
  if (Serial.available())
  {
    String cmd = Serial.readStringUntil('\n');
    if (cmd == "rst") {
      ESP.restart();
    } else if (cmd == "dsp") {
      Serial.println("Deep Sleep");
      esp_deep_sleep_start();
    } else if (cmd == "lsp") {
      Serial.println("Light Sleep");
      esp_light_sleep_start();
    } else {
      Serial.println("Unknown command");
    }
  }

  display.refreshScreen(); // OLED画面更新

  // ボタン状態更新
  for (auto &btn : buttons) btn.update();
}