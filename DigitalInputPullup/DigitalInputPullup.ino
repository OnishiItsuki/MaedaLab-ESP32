/*
  Input Pull-up Test for ESP32 (library : ESP32-Dev Module)

  This example demonstrates the use of gpio_set_pull_mode(GPIO_NUM_*, GPIO_*)).
  It reads a digital input on pin 22.

  The circuit:
  - Oscilloscope is connected to pin 22 named by GPIO_NUM_22 as ESP32 oriented name

  Unlike pinMode(INPUT), there is no pull-down resistor necessary. An internal
  45K-ohm resistor is pulled to 3.3V. This configuration causes the input to read
  HIGH when the switch is open, and LOW when it is closed.

  created 4 Mar 2021
  by Masahiro Furukawa

  This example code is in the public domain.

  reference:
  Basis of I2C
  https://kurobekoblog.com/arduino_i2c
  https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/i2c.html
  
  https://blog.goo.ne.jp/jh7ubc/e/cc27b64dd37726f33694d071c3b3a2d8
  https://qiita.com/MergeCells/items/20c3c1a0adfb222a19cd

  Oscilloscope : DSP_Quad
  https://wiki.seeedstudio.com/DSO_Quad/

*/

#include <Wire.h>

/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com
*********/

#include <Wire.h>

// https://randomnerdtutorials.com/esp32-i2c-communication-arduino-ide/
void setup() {
  Wire.begin();
  Serial.begin(115200);
  Serial.println("\nI2C Scanner");
}

void loop() {
  byte error, address;
  int nDevices;
  Serial.println("Scanning...");
  nDevices = 0;
  for (address = 1; address < 127; address++ ) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
      nDevices++;
    }
    else if (error == 4) {
      Serial.print("Unknow error at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0) {
    Serial.println("No I2C devices found\n");
  }
  else {
    Serial.println("done\n");
  }
  delay(500);
}

#if 0
void setup() {
  Wire.begin();

  //configure pin 2 as an input and enable the internal pull-up resistor
  pinMode(21, OPEN_DRAIN | INPUT);
  pinMode(22, OPEN_DRAIN | INPUT);
  //  pinMode(21, INPUT);
}

byte val = 0x1E;

void loop() {


  val++;        // increment value
  if (val == 64) // if reached 64th position (max)
  {
    val = 0;    // start over from lowest value
  }

  //  gpio_set_pull_mode(GPIO_NUM_21, GPIO_PULLUP_ONLY);
  //  delay(1);
  //
  //  Wire.beginTransmission(0x1E);
  //  Wire.write(val);
  //  Wire.endTransmission();
  //  delay(1);
  //
  //  gpio_set_pull_mode(GPIO_NUM_21, GPIO_PULLDOWN_ONLY);
  //  delay(1);
  //
  //  Wire.beginTransmission(0x1E);
  //  Wire.write(val);
  //  Wire.endTransmission();
  //  delay(1);
  //
  //  gpio_set_pull_mode(GPIO_NUM_21, GPIO_PULLUP_PULLDOWN);
  //  delay(1);
  //
  //  Wire.beginTransmission(0x1E);
  //  Wire.write(val);
  //  Wire.endTransmission();
  //  delay(1);

  gpio_set_pull_mode(GPIO_NUM_21, GPIO_FLOATING);
  gpio_set_pull_mode(GPIO_NUM_22, GPIO_FLOATING);
  Wire.beginTransmission(0x1E);
  //  Wire.write(val);
  //  Wire.write(val);
  //  Wire.write(val);
  //  Wire.write(val);
  //  Wire.write(val);
  //  Wire.write(val);
  Wire.endTransmission();
  delay(5);

}


#endif
