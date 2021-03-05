// Masahiro Furukawa
// Mar 6, 2021

// I2C Slave in Seeeduino XIAO

// reference : 

// I2C Slave
// https://qiita.com/hikoalpha/items/7bf563ee286a59bfd2f4

// Seeeduino XIAO のI2Cは SDA:A4, SCL:A5 です。
// https://zoe6120.com/2020/05/05/1449/

#include <Wire.h>

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
