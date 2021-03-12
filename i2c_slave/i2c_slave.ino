#include <Arduino.h>
#include <Wire.h>
//#include <WireSlave.h>

#define SLAVE_ADDR 0x1E
#define SDA_PIN 21
#define SCL_PIN 22

//void requestEvent();

//void setup()
//{
//    Serial.begin(115200);
//
//    bool res = WireSlave.begin(SDA_PIN, SCL_PIN, SLAVE_ADDR);
//    if (!res) {
//        Serial.println("I2C slave init failed");
//        while(1) delay(100);
//    }
//
//    WireSlave.onRequest(requestEvent);
//    Serial.printf("Slave joined I2C bus with addr #%d\n", SLAVE_ADDR);
//}
//
//void loop()
//{
//    WireSlave.update();
//    delay(1);
//}
//
//void requestEvent()
//{
//    static byte y = 0;
//
//    WireSlave.print("y is ");
//    WireSlave.write(y++);
//    Serial.print("send y is ");
//    Serial.println(y);
//}

byte b=0;

void setup() {
  Wire.begin(8);// Slave ID #8
  Wire.onRequest(requestEvent);
}

void loop() {
}

void requestEvent() {
  Wire.write(b++);
}
