#include <Wire.h>

#define SLAVE_ADDR 0x0E

byte b=0;

void setup() {
  Serial.begin(115200);
  Wire.begin(SLAVE_ADDR);// Slave ID #8
  Wire.onRequest(requestEvent);
  Serial.print("---start---");
}

void loop() {
  Serial.print("wait....");
  Serial.println(b);
  delay(500);
}

void requestEvent() {
  Serial.println(b);
  Wire.write(SLAVE_ADDR);
  Wire.write(b++);
  Wire.write(b++);
}
