#include <Arduino.h>

#ifndef SIGNAL_LED_PIN
#define SIGNAL_LED_PIN 25
#endif

void LED_init() {
  pinMode(SIGNAL_LED_PIN, OUTPUT);
}

void led_on() {
  digitalWrite(SIGNAL_LED_PIN, HIGH);
}

void led_off() {
  digitalWrite(SIGNAL_LED_PIN, LOW);
}
