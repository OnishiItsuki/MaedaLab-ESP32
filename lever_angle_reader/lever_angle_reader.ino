// 2021/02/22
// Itsuki Onishi
// onishi.itsuki@ist.osaka-u.ac.jp
//
// This is conrolling program of
//   * AD converter (LTC2309)
//   * OLED display (SSD1306)
//   * SIGNAL LED
// for ESP32.
// At first, include package for ESP32.
// See: https://github.com/espressif/arduino-esp32
//      https://dandydot.no-ip.biz/~dot/presen/advtech/seminars/iot_workshop/install-esp32-board-manager/README.md.html

#include <Arduino.h>

#define SDA_PIN 21
#define SCL_PIN 22
#define SIGNAL_LED_PIN 27
#define NUM_CH 6

int voltage_buffer[NUM_CH];

// step 1
void setup()
{
  // Serial initialization must be located before device initialization process because
  // functions in the other files use Serial communication.
  Serial.begin(115200);
  Serial.println();

  // device initialization
  ADC_init();
  LED_init();
  OLED_init();
  UDP_init();
}

void loop()
{
  read_voltage_from_ADC(voltage_buffer); // step 2 and 3, ADC_controller
  send_udp_signal(voltage_buffer);       // step 4 and 5, UDP_Tx
}
