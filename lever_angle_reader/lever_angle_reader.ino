//2021/11/01
//Itsuki Onishi
//onishi.itsuki@ist.osaka-u.ac.jp
//
//This is conroling program of
//  * AD converter (LTC2309)
//  * OLED display (SSD1306)
//  * SIGNAL LED
//for ESP32.
//At first, include package for ESP32.
//See: https://github.com/espressif/arduino-esp32
//     https://dandydot.no-ip.biz/~dot/presen/advtech/seminars/iot_workshop/install-esp32-board-manager/README.md.html
     

#include <Arduino.h>

#define SDA_PIN 21
#define SCL_PIN 22


void setup() {
  LED_init();
  OLED_init();
}

void loop() {
  disp_add_string(0, 0, "test");
  disp_add_string(0, 20, "test2");
  led_on();
  delay(1000);

  disp_clear();
  led_off();
  delay(1000);
}
