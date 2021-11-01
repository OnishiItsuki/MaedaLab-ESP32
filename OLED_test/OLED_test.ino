#include <Arduino.h>
#include <Wire.h>

// search "SSD1306 esp32" and istall top library
#include <SSD1306.h>

#define SDA_PIN 21
#define SCL_PIN 22
#define OLED_ADDR 0x3c
#define DISP_WIDTH 128
#define DISP_HEIGHT 64

SSD1306  display(OLED_ADDR, SDA_PIN, SCL_PIN);
int counter = 0;

void setup() {
}


void loop() {
  int r = counter % DISP_WIDTH;
  int c = counter % DISP_HEIGHT;
  
  display.init();
  display.setFont(ArialMT_Plain_16);
  display.drawString(r, c, String(counter++));
  display.display();
  delay(100);
}
