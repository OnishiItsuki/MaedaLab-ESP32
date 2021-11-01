#include <Arduino.h>
#include <Wire.h>

#ifndef SDA_PNT
#define SDA_PIN 21
#endif

#ifndef SCL_PIN
#define SCL_PIN 22
#endif

// ADC wait 7bit address but Wire.h send 16bit.
// Following implementation cam have bugs.
#define ADC_ADDR 0x08
