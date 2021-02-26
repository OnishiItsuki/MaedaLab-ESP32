#include <Arduino.h>
#include <Wire.h>
#include <WireSlave.h>

#define SLAVE_ADDR 0x1E
#define SDA_PIN 21
#define SCL_PIN 22

void requestEvent();

void setup()
{
    Serial.begin(115200);

    bool res = WireSlave.begin(SDA_PIN, SCL_PIN, SLAVE_ADDR);
    if (!res) {
        Serial.println("I2C slave init failed");
        while(1) delay(100);
    }

    WireSlave.onRequest(requestEvent);
    Serial.printf("Slave joined I2C bus with addr #%d\n", SLAVE_ADDR);
}

void loop()
{
    // the slave response time is directly related to how often
    // this update() method is called, so avoid using long delays
    // inside loop(), and be careful with time-consuming tasks
    WireSlave.update();

    // let I2C and other ESP32 peripherals interrupts work
    delay(1);
}

// function that runs whenever the master sends an empty packet.
// this function is registered as an event, see setup().
// do not perform time-consuming tasks inside this function,
// do them elsewhere and simply read the data you wish to
// send inside here.
void requestEvent()
{
    static byte y = 0;

    WireSlave.print("y is ");
    WireSlave.write(y++);
    Serial.print("send y is ");
    Serial.println(y);
}
