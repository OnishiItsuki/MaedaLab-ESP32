// Construction machine controler for ESP32-WROVER-B
// Itsuki Onishi
// October 2020

#include<stdio.h>
#include "Ticker.h"

#define START_BYTE 0x0f
#define SAMPLING_PERIOD 5.0f  // scale is ms
#define BYTE_A 2*i
#define BYTE_B 2*i+1

#define PATHNAME_SIZE 512

uint8_t buffer[8];

int outputBuffer[12];  // for setting output 0 or 1 to each Digital
int bufferIndex = 0;
int outProcCounter = 0;
int outProcFlag = 0;

//Ticker ticker;
//Ticker input_test_data;

// set output pins
// right side
int boomOutA = 15;
int boomOutB = 2;
int armOutA = 0;
int armOutB = 4;
int bucketOutA = 16;
int bucketOutB = 17;
// left side
int slewingOutA = 12;
int slewingOutB = 14;
int rightWheelOutA = 27;
int rightWheelOutB = 26;
int leftWheelOutA = 25;
int leftWheelOutB = 33;


void set_test_buffer(void)
{
    buffer[0] = 31;
    buffer[1] = 30;
    buffer[2] = 20;
    buffer[3] = 10;
    buffer[4] = 228;
    buffer[5] = 178;
    buffer[6] = 138;
    buffer[7] = 248;
}


void set_output(void)
{
  digitalWrite(boomOutA, outputBuffer[0]);
  digitalWrite(boomOutB, outputBuffer[1]);
  digitalWrite(armOutA, outputBuffer[2]);
  digitalWrite(armOutB, outputBuffer[3]);
  digitalWrite(bucketOutA, outputBuffer[4]);
  digitalWrite(bucketOutB, outputBuffer[5]);
  digitalWrite(slewingOutA, outputBuffer[6]);
  digitalWrite(slewingOutB, outputBuffer[7]);
  digitalWrite(rightWheelOutA, outputBuffer[8]);
  digitalWrite(rightWheelOutB, outputBuffer[9]);
  digitalWrite(leftWheelOutA, outputBuffer[10]);
  digitalWrite(leftWheelOutB, outputBuffer[11]);
}


void setup()
{
  // initialize pins
  pinMode(boomOutA, OUTPUT);
  pinMode(boomOutB, OUTPUT);
  pinMode(armOutA, OUTPUT);
  pinMode(armOutB, OUTPUT);
  pinMode(bucketOutA, OUTPUT);
  pinMode(bucketOutB, OUTPUT);
  pinMode(slewingOutA, OUTPUT);
  pinMode(slewingOutB, OUTPUT);
  pinMode(rightWheelOutA, OUTPUT);
  pinMode(rightWheelOutB, OUTPUT);
  pinMode(leftWheelOutA, OUTPUT);
  pinMode(leftWheelOutB, OUTPUT);
  
  for(int i=0; i<8; i++) {
    buffer[i] = 0;
  }
  for(int i=0; i<6; i++) {
    outputBuffer[BYTE_A] = LOW;
    outputBuffer[BYTE_B] = HIGH;
  }
  set_output();

  // initalize serial port
  Serial.begin(9600);
  int test_count = 0;

  // initial state is free run
  Serial.println("+");
//  ticker.attach_us(SAMPLING_PERIOD/128.0f, PWM_processor);
//  input_test_data.attach_us(SAMPLING_PERIOD, set_test_buffer);

}


void PWM_processor(void)
{
    for(int i=0; i<6; i++) {
        if((buffer[i+1]==0) || (buffer[i+1]==128)) {
            outputBuffer[BYTE_A] = LOW;
            outputBuffer[BYTE_B] = LOW;
            continue;
        }

        if(buffer[i+1]>128) {
            outputBuffer[BYTE_A] = LOW;
            outputBuffer[BYTE_B] = HIGH;
        } else {
            outputBuffer[BYTE_A] = HIGH;
            outputBuffer[BYTE_B] = LOW;
        }

        // decrement
        if (buffer[i+1] > 0)
            buffer[i+1]--;
    }
    set_output();
}


void event_func(void)
{

  // For test
  bufferIndex = 8;
  for(int i=0; i<8; i++){
    Serial.println("%d:%d ", i, buffer[i]);
  }
  uint8_t rx = buffer[0];
  // end of code for test

//        uint8_t rx = pc.getc();
//
//  wait start byte
  if(bufferIndex == 0 && rx != START_BYTE) {
    Serial.println("start byte ERROR");
    return;
  }

//        // push serial to buffer
//        buffer[bufferIndex++] = rx;

//  when buffer is full
  if(bufferIndex == 8) {
    bufferIndex = 0;

//    check parity
//    uint8_t serialXOR = buffer[1];
//    for (int i=2; i<=6; i++) {
//      serialXOR ^= buffer[i];
//    }
//    if (serialXOR != buffer[7]) {
//      Serial.println("parity byte ERROR: XOR is %d, buffer byte is %d  ", serialXOR, buffer[7]);
//      return;
//    } else {
//      outProcFlag = 1;
//    }
  }
}

void loop()
{
//  if(pc.readable(){
    event_func();
    test_count++;
//  }

//code for test
  if(test_count%1000 == 0) {
    Serial.printf("+");
    test_count = 0;
  }
//end of code for test

    }
}
