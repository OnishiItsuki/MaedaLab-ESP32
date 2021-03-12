#include <Arduino.h>
#include <Wire.h>

//#define SDA_PIN 21
//#define SCL_PIN 22
#define SLAVE_ADDR 0x0E
#define SLAVE_ADDR_1 0x1E
#define LIST_LENGTH 1

#define MAX_SLAVE_RESPONSE_LENGTH 3

uint8_t SLAVE_LIST[LIST_LENGTH];

void setup() {
  SLAVE_LIST[0] = SLAVE_ADDR;
//  SLAVE_LIST[1] = SLAVE_ADDR_1;
  Wire.begin();
  Serial.begin(115200);
}

void loop() {
  byte s;
  uint8_t address;
  for (int i=0;i<LIST_LENGTH;i++)
  {
    address = SLAVE_LIST[i];
    s = Wire.requestFrom(address, MAX_SLAVE_RESPONSE_LENGTH);
  
    Serial.println("------start------");
    Serial.print("The number of items is ");
    Serial.println(s);
  
    while(Wire.available()) 
    {
      uint8_t c = Wire.read();
      Serial.println(c);
    }
    Serial.print("------end------\n\n");
  }
  delay(1000);
}
