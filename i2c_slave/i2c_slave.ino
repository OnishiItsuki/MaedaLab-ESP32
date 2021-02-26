#include <Wire.h>
#define SLAVE_ADDR 0x1E

void setup() {
  Wire.begin();

  Serial.begin(115200);
  Serial.println("\nI2C");
}

void loop() {
  Wire.requestFrom(SLAVE_ADDR, 1);
   while (Wire.available()) {
    byte b = Wire.read();
    Serial.println((uint8_t)b);
  }

  delay(500);
}
