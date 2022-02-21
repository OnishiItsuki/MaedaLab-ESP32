#include <Arduino.h>
#include <Wire.h>

#ifndef SDA_PNN
#define SDA_PIN 21
#endif

#ifndef SCL_PIN
#define SCL_PIN 22
#endif

// ADC wait 7bit address but Wire.h send 16bit.
// Following implementation cam have bugs.
#define ADC_ADDR 0x08

void ADC_init()
{
    Serial.println("ADC_init is not implemented");
}

void send_read_signal_to_ADC()
{
    Serial.println("send_read_signal_to_ADC is not implemented");
}

void read_voltage_from_ADC(uint8_t buffer[])  // voltage_buffer[NUM_CH]
{
    Serial.println("read_voltage_from_ADC is not implemented");
}
