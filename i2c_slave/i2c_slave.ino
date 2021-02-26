#include <Arduino.h>
#include <Wire.h>
#include <WireSlave.h>

#define SLAVE_ADDR 0x1E
#define SDA_PIN 21
#define SCL_PIN 22

void receiveEvent(int howMany);

void setup() {
  Serial.begin(115200);
  Serial.println("\nI2C");
  
  bool success = WireSlave.begin(SDA_PIN, SCL_PIN, SLAVE_ADDR);
  if (!success) {
    Serial.println("I2C slave init failed");
    while(1) delay(100);
  }

  WireSlave.onReceive(receiveEvent);
}

void loop() {
  WireSlave.update();
  
  delay(1);
}

void receiveEvent(int howMany)
{
  static byte y = 0;

  WireSlave.print("y is ");
  WireSlave.write(y++);
  Serial.print("send y is ");
  Serial.println(y);
}
