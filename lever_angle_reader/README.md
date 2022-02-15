# Library for ESP32

2022/02/15 \
Itsuki Onishi \
E-mail : onishi.itsuki@ist.osaka-u.ac.jp


## Functional description
This program controls following devices using ESP32.
  * AD converter (LTC2309)
  * OLED display (SSD1306)
  * SIGNAL LED

These devices requires some packages. \
Please see requirements for details.

The overview is following.
  1. Initialize ESP32, AD converter (LTC2309), OLED display (SSD1306), LED.
  2. Send signals to ADC for reading lever angle.
  3. Receive observed voltage values from ADC.
  4. Send observed voltage values to ESP32 running "PWM_motor_controller".

This program works with "PWM_motor_controller".

## Directory configuration
This program is constructed by following directories and files.
```  
.  
|-- documents
|   |-- LTC2309.pdf
|
|-- lever_angle_reader.ino      # Main
|-- ADC_controller.ino          # Functions for AD converter
|-- OLED_controller.ino         # Functions for OLED
|-- SIGNAL_LED_controller.ino   # Functions for Signal LED
|-- UDP_Tx.ino                  # Functions to send UDP communication
|-- function_variable_list.xlsx # List of functions and variables
--- README.md                   # This file
```


## Requirements
At first, install package for ESP32, see 
 * https://github.com/espressif/arduino-esp32
 * https://dandydot.no-ip.biz/~dot/presen/advtech/seminars/iot_workshop/install-esp32-board-manager/README.md.html .

\
Following libraries are required. \
Please see sites for details of libraries under library names.

  * ESP8266 and ESP32 driver for SSD1366 displays
    * https://wak-tech.com/archives/825
    * https://github.com/ThingPulse/esp8266-oled-ssd1306
