# Library for ESP32

2022/02/15 \
Itsuki Onishi \
E-mail : onishi.itsuki@ist.osaka-u.ac.jp


## Functional description
The overview is following.
  1. Initialize ESP32.
  2. Receive observed voltage values from ESP32 running "lever_angle_reader".
  3. Compute duty ratio from voltage values.
  4. Send PWM signals to motor.

This program works with "lever_angle_reader".

## Directory configuration
This program is constructed by following directories and files.
```  
.  
|-- PWM_motor_controller.ino    # Main
|-- PWM_controller.ino          # Functions for AD converter
|-- UPD_AP_Rx.ino               # Functions to receive UDP communication
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
