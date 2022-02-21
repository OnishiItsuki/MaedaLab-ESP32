#include <Arduino.h>
#include <Wire.h>

#ifndef SDA_PNN
#define SDA_PIN 21
#endif

#ifndef SCL_PIN
#define SCL_PIN 22
#endif

#define MAX_SLAVE_RESPONSE_LENGTH 3

// ADC wait 7bit address but Wire.h send 16bit.
// Following implementation may have bugs.
#define ADC_ADDR 0x08

void ADC_init()
{
    Serial.println("ADC_init is not implemented");
    // Wire.begin();
}

void _send_read_signal() // step2
{
    Serial.println("send_read_signal_to_ADC is not implemented");
}

void _receive_voltage_values(int buffer[]) // voltage_buffer[NUM_CH], step3
{
    Serial.println("receive_voltage_from_ADC is not implemented");
    Wire.requestFrom(ADC_ADDR, MAX_SLAVE_RESPONSE_LENGTH);
    for (int i = 0; i < NUM_CH; i++)
    {
        buffer[i] = Wire.read();
    }
}

void read_voltage_from_ADC(int buffer[]) // voltage_buffer[NUM_CH]
{
    _send_read_signal();             // step2
    _receive_voltage_values(buffer); // step3
}
