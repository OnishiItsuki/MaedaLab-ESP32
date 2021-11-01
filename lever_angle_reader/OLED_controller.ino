#include <Wire.h>

// search "SSD1306 esp32" and istall top library
// detail is on following
// https://wak-tech.com/archives/825
// https://github.com/ThingPulse/esp8266-oled-ssd1306
#include <SSD1306.h>

#ifndef SDA_PNT
#define SDA_PIN 21
#endif

#ifndef SCL_PIN
#define SCL_PIN 22
#endif

#define OLED_ADDR 0x3c
#define DISP_WIDTH 128
#define DISP_HEIGHT 64
#define FONT ArialMT_Plain_16

SSD1306  display(OLED_ADDR, SDA_PIN, SCL_PIN);

void OLED_init() {
  disp_all_pixel();
  delay(1000);
  disp_init();
}

void disp_init() {
  display.init();
  display.setFont(FONT);
}

void disp_clear() {
  disp_init();
}

void disp_all_pixel() {
  display.init();
  display.fillRect(0, 0, DISP_WIDTH, DISP_HEIGHT);
  display.display();
}

void disp_add_string(int16_t x, int16_t y, String message) {
  display.drawString(x, y, message);
  display.display();
}
