// Construction machine controler for ESP32-WROVER-B
// Itsuki Onishi
// October 2020

#include <Ticker.h>

#define START_BYTE 0x0f
#define SAMPLING_PERIOD 5.0f  // scale is ms
#define BYTE_A 2*i
#define BYTE_B 2*i+1

// set output pins
// right side
#define boomOutA 15
#define boomOutB 2
#define armOutA 0
#define armOutB 4
#define bucketOutA 13
#define bucketOutB 12
// left side
#define slewingOutA 14
#define slewingOutB 27
#define rightWheelOutA 26
#define rightWheelOutB 25
#define leftWheelOutA 33
#define leftWheelOutB 32

uint8_t buffer[8];  // This list stock input signal

int outputBuffer[12];  // This list hold Duty ratio on each pins
int bufferIndex = 0;  // This is the index of waiting sinal
int outProcCounter = 0;
int outProcFlag = 0;
int test_count = 0;

Ticker ticker;
Ticker input_test_data;  //for test


//  for test
void set_test_buffer(void)
{
    buffer[0] = 31;
    buffer[1] = 30;
    buffer[2] = 20;
    buffer[3] = 10;
    buffer[4] = 228;
    buffer[5] = 178;
    buffer[6] = 138;
    buffer[7] = 220;
}


// set duty ratio on each pins
void set_output(void)
{
  ledcWrite(0, outputBuffer[0]);
  ledcWrite(1, outputBuffer[1]);
  ledcWrite(2, outputBuffer[2]);
  ledcWrite(3, outputBuffer[3]);
  ledcWrite(4, outputBuffer[4]);
  ledcWrite(5, outputBuffer[5]);
  ledcWrite(6, outputBuffer[6]);
  ledcWrite(7, outputBuffer[7]);
  ledcWrite(8, outputBuffer[8]);
  ledcWrite(9, outputBuffer[9]);
  ledcWrite(10, outputBuffer[10]);
  ledcWrite(11, outputBuffer[11]);
}


void setup()
{
  // initialize pins
  ledcSetup(0, 115200, 7);
  ledcAttachPin(boomOutA, 0);
  ledcSetup(1, 115200, 7);
  ledcAttachPin(boomOutB, 1);
  ledcSetup(2, 115200, 7);
  ledcAttachPin(armOutA, 2);
  ledcSetup(3, 115200, 7);
  ledcAttachPin(armOutB, 3);
  ledcSetup(4, 115200, 7);
  ledcAttachPin(bucketOutA, 4);
  ledcSetup(5, 115200, 7);
  ledcAttachPin(bucketOutB, 5);
  ledcSetup(6, 115200, 7);
  ledcAttachPin(slewingOutA, 6);
  ledcSetup(7, 115200, 7);
  ledcAttachPin(slewingOutB, 7);
  ledcSetup(8, 115200, 7);
  ledcAttachPin(rightWheelOutA, 8);
  ledcSetup(9, 115200, 7);
  ledcAttachPin(rightWheelOutB, 9);
  ledcSetup(10, 115200, 7);
  ledcAttachPin(leftWheelOutA, 10);
  ledcSetup(11, 115200, 7);
  ledcAttachPin(leftWheelOutB, 11);

  // initial state is free run
  for(int i=0; i<8; i++) {
    buffer[i] = 0;
  }
  for(int i=0; i<6; i++) {
    outputBuffer[BYTE_A] = 0;
    outputBuffer[BYTE_B] = 0;
  }
  set_output();

  // initalize serial port
  Serial.begin(115200);
  Serial.println("+");

  // set tickers
  ticker.attach_ms(SAMPLING_PERIOD, PWM_processor);
  // for test
  input_test_data.attach_ms(SAMPLING_PERIOD, set_test_buffer);

}


//  control whitch pins (A or B) are LOW or HIGH on each DoF.
//  outputBuffer that is HIGH pin holds duty ratio.
void PWM_processor(void)
{
  for(int i=0; i<6; i++) {
    // buffer[0] is start byte, so input signals start from 1
    // Both pins is LOW when buffer is 0 or 128.
      if(buffer[i+1]>=128) {
          outputBuffer[BYTE_A] = 0;
          outputBuffer[BYTE_B] = buffer[i+1] - 128;
      } else {
          outputBuffer[BYTE_A] = buffer[i+1];
          outputBuffer[BYTE_B] = 0;
      }
      buffer[i+1] = 0;
  }
  set_output();
}


void loop()
{
  //  if(pc.readable(){ ??
  // For test
  bufferIndex = 8;
//    Serial.println("check buffer");
//    for(int i=0; i<8; i++){
//    Serial.println(i);
//    Serial.println(buffer[i]);
//  }
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

//  check parity
    uint8_t serialXOR = buffer[1];
    for (int i=2; i<=6; i++) {
      serialXOR ^= buffer[i];
    }
    if (serialXOR != buffer[7]) {
      Serial.print("parity byte ERROR: XOR is ");
      Serial.print(serialXOR);
      Serial.print(" buffer byte is ");
      Serial.println(buffer[7]);
      return;
    } else {
      outProcFlag = 1;
    }
  }
}
