/*=================================================================================== */
/* Ticker_ESP32/blinkLEDs.ino                                                         */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* A simple example that blinks 2 LEDs to demonstrate how to use the library          */
/*                                                                                    */
/* Created by Lyudmil Vladimirov, Sep 2017                                            */
/* More info: https://github.com/sglvladi/Ticker_ESP32                                */
/* ================================================================================== */

#include "Ticker.h"

#define LED1 12 // (LED1 pin: GPIO12)
#define LED2 14 // (LED2 pin: GPIO14)

// Use 1st timer of 4 (in range 0-3).
Ticker LED_Ticker_1(0);

// Use 2nd timer of 4 (in range 0-3).
Ticker LED_Ticker_2(1);

// Callback function to blink LED1
void blinkLED1(){
    int currentLEDState = digitalRead(LED1);
    digitalWrite(LED1, !currentLEDState);
}

// Callback function to blink LED2
void blinkLED2(){
    int currentLEDState = digitalRead(LED2);
    digitalWrite(LED2, !currentLEDState);
}

void setup() {

  // Initiate LEDs as OUTPUTs (IMPORTANT!!!)
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  
  // Blink first LED every 0.5 seconds
  LED_Ticker_1.attach(0.5, blinkLED1);

  // Blink second LED every 100000 microseconds (0.1 sec)
  LED_Ticker_2.attach_us(100000, blinkLED2);

  // Let the tickers run for 10 sec and detach
  unsigned long start = millis();
  while(millis()-start < 10000){
    yield();
  }
  
  LED_Ticker_1.detach();
  LED_Ticker_2.detach();

  // Swap LED flashing speeds and restart tickers
  // ===========================================>
  
  // Blink first LED every 0.1 seconds
  LED_Ticker_1.attach(0.1, blinkLED1);

  // Blink second LED every 500000 microseconds (0.5 sec)
  LED_Ticker_2.attach_us(500000, blinkLED2);

  // Let the tickers run for 10 sec and detach
  start = millis();
  while(millis()-start < 10000){
    yield();
  }
  
  LED_Ticker_1.detach();
  LED_Ticker_2.detach();
  
}

void loop() {
  // put your main code here, to run repeatedly:

}